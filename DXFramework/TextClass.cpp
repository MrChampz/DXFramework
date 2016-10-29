/////////////////////////////////////////////
//	Filename: TextClass.cpp
/////////////////////////////////////////////
#include "TextClass.h"

TextClass::TextClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_vertexBuffer2 = 0;
	m_indexBuffer2 = 0;
}

TextClass::TextClass(const TextClass& other)
{
}

TextClass::~TextClass()
{
}

bool TextClass::Initialize(ID3D10Device* device, int screenWidth, int screenHeight, int maxLength,
	bool shadow, FontClass* Font, char* text, int positionX, int positionY, float red, float green, float blue)
{
	bool result;

	// Store the screen width and height.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the maximum length of the sentence.
	m_maxLength = maxLength;

	// Store if this sentence is shadowed or not.
	m_shadow = shadow;

	// Initalize the sentence.
	result = InitializeSentence(device, Font, text, positionX, positionY, red, green, blue);
	if (!result)
	{
		return false;
	}

	return true;
}

void TextClass::Shutdown()
{
	// Release the buffers.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	if (m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer2)
	{
		m_vertexBuffer2->Release();
		m_vertexBuffer2 = 0;
	}

	if (m_indexBuffer2)
	{
		m_indexBuffer2->Release();
		m_indexBuffer2 = 0;
	}

	return;
}

void TextClass::Render(ID3D10Device* device, ShaderManagerClass* ShaderManager, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX orthoMatrix, ID3D10ShaderResourceView* fontTexture)
{
	// Draw the sentence.
	RenderSentence(device, ShaderManager, worldMatrix, viewMatrix, orthoMatrix, fontTexture);

	return;
}

bool TextClass::InitializeSentence(ID3D10Device* device, FontClass* Font, char* text, int positionX,
	int positionY, float red, float green, float blue)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D10_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D10_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Set the vertex and index count.
	m_vertexCount = 6 * m_maxLength;
	m_indexCount = 6 * m_maxLength;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// Initialize the index array.
	for (i = 0; i<m_indexCount; i++)
	{
		indices[i] = i;
	}

	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D10_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D10_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D10_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// If shadowed create the second vertex and index buffer.
	if (m_shadow)
	{
		result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer2);
		if (FAILED(result))
		{
			return false;
		}

		result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer2);
		if (FAILED(result))
		{
			return false;
		}
	}

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;

	// Release the index array as it is no longer needed.
	delete[] indices;
	indices = 0;

	// Now add the text data to the sentence buffers.
	result = UpdateSentence(device, Font, text, positionX, positionY, red, green, blue);
	if (!result)
	{
		return false;
	}

	return true;
}

bool TextClass::UpdateSentence(ID3D10Device* device, FontClass* Font, char* text, int positionX, int positionY, float red,
	float green, float blue)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	void* mappedResource;
	void* verticesPtr;
	HRESULT result;


	// Store the color of the sentence.
	m_pixelColor = XMFLOAT4(red, green, blue, 1.0f);

	// Get the number of letters in the sentence.
	numLetters = (int)strlen(text);

	// Check for possible buffer overflow.
	if (numLetters > m_maxLength)
	{
		return false;
	}

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	// Calculate the X and Y pixel position on the screen to start drawing to.
	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);

	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

	// Lock the vertex buffer.
	result = m_vertexBuffer->Map(D3D10_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result))
	{
		return false;
	}

	// Get a pointer to the mapped resource data pointer.
	verticesPtr = (void*)mappedResource;

	// Copy the vertex array into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	// Unlock the vertex buffer.
	m_vertexBuffer->Unmap();

	// If shadowed then do the same for the second vertex buffer but offset by two pixels on both axis.
	if (m_shadow)
	{
		memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

		drawX = (float)((((m_screenWidth / 2) * -1) + positionX) + 2);
		drawY = (float)(((m_screenHeight / 2) - positionY) - 2);
		Font->BuildVertexArray((void*)vertices, text, drawX, drawY);

		result = m_vertexBuffer2->Map(D3D10_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
		{
			return false;
		}
		verticesPtr = (void*)mappedResource;
		memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));
		m_vertexBuffer2->Unmap();
	}

	// Release the vertex array as it is no longer needed.
	delete[] vertices;
	vertices = 0;

	return true;
}

void TextClass::RenderSentence(ID3D10Device* device, ShaderManagerClass* ShaderManager, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX orthoMatrix, ID3D10ShaderResourceView* fontTexture)
{
	unsigned int stride, offset;
	XMFLOAT4 shadowColor;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType);
	offset = 0;

	// If shadowed then render the shadow text first.
	if (m_shadow)
	{
		shadowColor = XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f);

		device->IASetVertexBuffers(0, 1, &m_vertexBuffer2, &stride, &offset);
		device->IASetIndexBuffer(m_indexBuffer2, DXGI_FORMAT_R32_UINT, 0);
		device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		ShaderManager->RenderFontShader(device, m_indexCount, worldMatrix, viewMatrix, orthoMatrix, fontTexture, shadowColor);
	}

	// Render the text buffers.
	device->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	device->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	device->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	ShaderManager->RenderFontShader(device, m_indexCount, worldMatrix, viewMatrix, orthoMatrix, fontTexture, m_pixelColor);

	return;
}