/////////////////////////////////////////////
//	Filename: ClipPlaneShaderClass.cpp
/////////////////////////////////////////////
#include "ClipPlaneShaderClass.h"

ClipPlaneShaderClass::ClipPlaneShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_sampleState = 0;
	m_matrixBuffer = 0;
	m_clipPlaneBuffer = 0;
}

ClipPlaneShaderClass::ClipPlaneShaderClass(const ClipPlaneShaderClass& other)
{
}

ClipPlaneShaderClass::~ClipPlaneShaderClass()
{
}

bool ClipPlaneShaderClass::Initialize(ID3D10Device* device, HWND hwnd)
{
	bool result;

	// Initialize the vertex and pixel shaders
	result = InitializeShader(device, hwnd, L"Shaders/ClipPlane.vs", L"Shaders/ClipPlane.ps");
	if (!result)
	{
		return false;
	}

	return true;
}

void ClipPlaneShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects
	ShutdownShader();

	return;
}

bool ClipPlaneShaderClass::Render(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, XMFLOAT4 clipPlane)
{
	bool result;

	// Set the shader parameters that it will use for rendering
	result = SetShaderParameters(device, worldMatrix, viewMatrix, projectionMatrix, texture, clipPlane);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader
	RenderShader(device, indexCount);

	return true;
}

bool ClipPlaneShaderClass::InitializeShader(ID3D10Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D10_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D10_SAMPLER_DESC samplerDesc;
	D3D10_BUFFER_DESC matrixBufferDesc;
	D3D10_BUFFER_DESC clipPlaneBufferDesc;

	// Initialize the pointers this function will use to null
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// Compile the vertex shader code
	result = D3DCompileFromFile(vsFilename, NULL, NULL, "ClipPlaneVertexShader", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&vertexShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, vsFilename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself
		else
		{
			MessageBox(hwnd, vsFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Compile the pixel shader code
	result = D3DCompileFromFile(psFilename, NULL, NULL, "ClipPlanePixelShader", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
		&pixelShaderBuffer, &errorMessage);
	if (FAILED(result))
	{
		// If the shader failed to compile it should have writen something to the error message
		if (errorMessage)
		{
			OutputShaderErrorMessage(errorMessage, hwnd, psFilename);
		}
		// If there was nothing in the error message then it simply could not find the shader file itself
		else
		{
			MessageBox(hwnd, psFilename, L"Missing Shader File", MB_OK);
		}

		return false;
	}

	// Create the vertex shader from the buffer
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_vertexShader);
	if (FAILED(result))
	{
		return false;
	}

	// Create the pixel shader from the buffer
	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), &m_pixelShader);
	if (FAILED(result))
	{
		return false;
	}

	// Create the vertex input layout description
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "TEXCOORD";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	//  Get a count of the elements in the layout
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	// Create the vertex input layout
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_layout);
	if (FAILED(result))
	{
		return false;
	}

	// Release the vertex shader buffer and pixel shader buffer since they are no longer needed
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;

	// Create a texture sampler state description
	samplerDesc.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU = D3D10_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D10_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D10_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0.0f;
	samplerDesc.MaxAnisotropy = 1;
	samplerDesc.ComparisonFunc = D3D10_COMPARISON_ALWAYS;
	samplerDesc.BorderColor[0] = 0;
	samplerDesc.BorderColor[1] = 0;
	samplerDesc.BorderColor[2] = 0;
	samplerDesc.BorderColor[3] = 0;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D10_FLOAT32_MAX;

	// Create the texture sampler state
	result = device->CreateSamplerState(&samplerDesc, &m_sampleState);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the description of the dynamic matrix constant buffer that is in the vertex shader
	matrixBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;

	// Create the constant buffer pointer so we can acess the vertex shader constant buffer from within this class
	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Setup the description of the dynamic clip plane constant buffer that is in the vertex shader
	clipPlaneBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	clipPlaneBufferDesc.ByteWidth = sizeof(ClipPlaneBufferType);
	clipPlaneBufferDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
	clipPlaneBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	clipPlaneBufferDesc.MiscFlags = 0;

	// Create the constant buffer pointer so we can acess the vertex shader constant buffer from within this class
	result = device->CreateBuffer(&clipPlaneBufferDesc, NULL, &m_clipPlaneBuffer);
	if (FAILED(result))
	{
		return false;
	}

	return true;
}

void ClipPlaneShaderClass::ShutdownShader()
{
	// Release the clip plane constant buffer
	if (m_clipPlaneBuffer)
	{
		m_clipPlaneBuffer->Release();
		m_clipPlaneBuffer = 0;
	}

	// Release the matrix constant buffer
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	// Release the sampler state
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	// Release the layout
	if (m_layout)
	{
		m_layout->Release();
		m_layout = 0;
	}

	// Release the pixel shader
	if (m_pixelShader)
	{
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	// Release the vertex shader
	if (m_vertexShader)
	{
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
}

void ClipPlaneShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
{
	char* compileErrors;
	unsigned long long bufferSize, i;
	ofstream fout;

	// Get a pointer to the error message text buffer
	compileErrors = (char*)(errorMessage->GetBufferPointer());

	// Get the length of the message
	bufferSize = errorMessage->GetBufferSize();

	// Open a file to write the error message to
	fout.open("shader-error.txt");

	// Write out the error message
	for (i = 0; i < bufferSize; i++)
	{
		fout << compileErrors[i];
	}

	// Close the file
	fout.close();

	// Release the error message
	errorMessage->Release();
	errorMessage = 0;

	// Pop a message up on the screen to notify the user to check the text file for compile errors
	MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for message.", shaderFilename, MB_OK);

	return;
}

bool ClipPlaneShaderClass::SetShaderParameters(ID3D10Device* device, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, XMFLOAT4 clipPlane)
{
	HRESULT result;
	void* mappedResource;
	MatrixBufferType* dataPtr;
	ClipPlaneBufferType* dataPtr2;
	unsigned int bufferNumber;

	// Transpose the matrices to prepare them for the shader
	worldMatrix = XMMatrixTranspose(worldMatrix);
	viewMatrix = XMMatrixTranspose(viewMatrix);
	projectionMatrix = XMMatrixTranspose(projectionMatrix);

	// Lock the constant buffer so it can be written to
	result = m_matrixBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer
	dataPtr = (MatrixBufferType*)mappedResource;

	// Copy the matrices into the constant buffer
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	// Unlock the constant buffer
	m_matrixBuffer->Unmap();

	// Set the position of the constant buffer in the vertex shader
	bufferNumber = 0;

	// Finanly set the constant buffer in the vertex shader with the updated values
	device->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	// Lock the constant buffer so it can be written to
	result = m_clipPlaneBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer
	dataPtr2 = (ClipPlaneBufferType*)mappedResource;

	// Copy the matrices into the constant buffer
	dataPtr2->clipPlane = clipPlane;

	// Unlock the constant buffer
	m_clipPlaneBuffer->Unmap();

	// Set the position of the constant buffer in the vertex shader
	bufferNumber = 1;

	// Finanly set the constant buffer in the vertex shader with the updated values
	device->VSSetConstantBuffers(bufferNumber, 1, &m_clipPlaneBuffer);

	// Set shader texture resource in the pixel shader
	device->PSSetShaderResources(0, 1, &texture);

	return true;
}

void ClipPlaneShaderClass::RenderShader(ID3D10Device* device, int indexCount)
{
	// Set the vertex input layout
	device->IASetInputLayout(m_layout);

	// Set the vertex and pixel shaders that will be used to render this triangle
	device->VSSetShader(m_vertexShader);
	device->PSSetShader(m_pixelShader);

	// Set the sampler state in the pixel shader
	device->PSSetSamplers(0, 1, &m_sampleState);

	// Render the triangle
	device->DrawIndexed(indexCount, 0, 0);

	return;
}