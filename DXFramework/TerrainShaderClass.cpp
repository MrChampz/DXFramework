/////////////////////////////////////////////
//	Filename: TerrainShaderClass.cpp
/////////////////////////////////////////////
#include "TerrainShaderClass.h"

TerrainShaderClass::TerrainShaderClass()
{
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
	m_sampleState = 0;
	m_lightBuffer = 0;
}

TerrainShaderClass::TerrainShaderClass(const TerrainShaderClass& other)
{
}

TerrainShaderClass::~TerrainShaderClass()
{
}

bool TerrainShaderClass::Initialize(ID3D10Device* device, HWND hwnd)
{
	bool result;

	// Initialize the vertex and pixel shaders
	result = InitializeShader(device, hwnd, L"Shaders/Terrain.vs", L"Shaders/Terrain.ps");
	if (!result)
	{
		return false;
	}

	return true;
}

void TerrainShaderClass::Shutdown()
{
	// Shutdown the vertex and pixel shaders as well as the related objects
	ShutdownShader();

	return;
}

bool TerrainShaderClass::Render(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, ID3D10ShaderResourceView* normalMap, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	bool result;

	// Set the shader parameters that it will use for rendering
	result = SetShaderParameters(device, worldMatrix, viewMatrix, projectionMatrix, texture, normalMap, lightDirection,
		diffuseColor);
	if (!result)
	{
		return false;
	}

	// Now render the prepared buffers with the shader
	RenderShader(device, indexCount);

	return true;
}

bool TerrainShaderClass::InitializeShader(ID3D10Device* device, HWND hwnd, WCHAR* vsFilename, WCHAR* psFilename)
{
	HRESULT result;
	ID3D10Blob* errorMessage;
	ID3D10Blob* vertexShaderBuffer;
	ID3D10Blob* pixelShaderBuffer;
	D3D10_INPUT_ELEMENT_DESC polygonLayout[6];
	unsigned int numElements;
	D3D10_BUFFER_DESC matrixBufferDesc;
	D3D10_BUFFER_DESC lightBufferDesc;
	D3D10_SAMPLER_DESC samplerDesc;

	// Initialize the pointers this function will use to null
	errorMessage = 0;
	vertexShaderBuffer = 0;
	pixelShaderBuffer = 0;

	// Compile the vertex shader code
	result = D3DCompileFromFile(vsFilename, NULL, NULL, "TerrainVertexShader", "vs_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
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
	result = D3DCompileFromFile(psFilename, NULL, NULL, "TerrainPixelShader", "ps_4_0", D3D10_SHADER_ENABLE_STRICTNESS, 0,
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

	polygonLayout[2].SemanticName = "NORMAL";
	polygonLayout[2].SemanticIndex = 0;
	polygonLayout[2].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[2].InputSlot = 0;
	polygonLayout[2].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[2].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[2].InstanceDataStepRate = 0;

	polygonLayout[3].SemanticName = "TANGENT";
	polygonLayout[3].SemanticIndex = 0;
	polygonLayout[3].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[3].InputSlot = 0;
	polygonLayout[3].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[3].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[3].InstanceDataStepRate = 0;

	polygonLayout[4].SemanticName = "BINORMAL";
	polygonLayout[4].SemanticIndex = 0;
	polygonLayout[4].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[4].InputSlot = 0;
	polygonLayout[4].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[4].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[4].InstanceDataStepRate = 0;

	polygonLayout[5].SemanticName = "COLOR";
	polygonLayout[5].SemanticIndex = 0;
	polygonLayout[5].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[5].InputSlot = 0;
	polygonLayout[5].AlignedByteOffset = D3D10_APPEND_ALIGNED_ELEMENT;
	polygonLayout[5].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;
	polygonLayout[5].InstanceDataStepRate = 0;

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

	// Setup the description of the matrix dynamic constant buffer that is in the vertex shader
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

	// Setup the description of the dynamic light constant buffer that is in the pixel shader
	lightBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	lightBufferDesc.ByteWidth = sizeof(LightBufferType);
	lightBufferDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	lightBufferDesc.MiscFlags = 0;

	// Create the constant buffer pointer so we can acess the pixel shader constant buffer from within this class
	result = device->CreateBuffer(&lightBufferDesc, NULL, &m_lightBuffer);
	if (FAILED(result))
	{
		return false;
	}

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

	return true;
}

void TerrainShaderClass::ShutdownShader()
{
	// Release the sampler state
	if (m_sampleState)
	{
		m_sampleState->Release();
		m_sampleState = 0;
	}

	// Release the light constant buffer
	if (m_lightBuffer)
	{
		m_lightBuffer->Release();
		m_lightBuffer = 0;
	}

	// Release the matrix constant buffer
	if (m_matrixBuffer)
	{
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
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

void TerrainShaderClass::OutputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFilename)
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

bool TerrainShaderClass::SetShaderParameters(ID3D10Device* device, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, ID3D10ShaderResourceView* normalMap, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	HRESULT result;
	void* mappedResource;
	unsigned int bufferNumber;
	MatrixBufferType* dataPtr;
	LightBufferType* dataPtr2;

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

	// Set shader texture resources in the pixel shader
	device->PSSetShaderResources(0, 1, &texture);
	device->PSSetShaderResources(1, 1, &normalMap);

	// Lock the light constant buffer so it can be written to
	result = m_lightBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the constant buffer
	dataPtr2 = (LightBufferType*)mappedResource;

	// Copy the lighting variables into the constant buffer
	dataPtr2->diffuseColor = diffuseColor;
	dataPtr2->lightDirection = lightDirection;
	dataPtr2->padding = 0.0f;

	// Unlock the constant buffer
	m_lightBuffer->Unmap();

	// Set the position of the light constant buffer in the pixel shader.
	bufferNumber = 0;

	// Finally set the light constant buffer in the pixel shader with the updated values.
	device->PSSetConstantBuffers(bufferNumber, 1, &m_lightBuffer);

	return true;
}

void TerrainShaderClass::RenderShader(ID3D10Device* device, int indexCount)
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