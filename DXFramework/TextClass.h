/////////////////////////////////////////////
//	Filename: TextClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "FontClass.h"
#include "ShaderManagerClass.h"

/////////////////////////////////////////////
//	Class name: TextClass
/////////////////////////////////////////////
class TextClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D10Device*, int, int, int, bool, FontClass*, char*, int, int, float, float, float);
	void Shutdown();
	void Render(ID3D10Device*, ShaderManagerClass*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*);

	bool UpdateSentence(ID3D10Device*, FontClass*, char*, int, int, float, float, float);

private:
	bool InitializeSentence(ID3D10Device*, FontClass*, char*, int, int, float, float, float);
	void RenderSentence(ID3D10Device*, ShaderManagerClass*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*);

private:
	ID3D10Buffer *m_vertexBuffer, *m_indexBuffer, *m_vertexBuffer2, *m_indexBuffer2;
	int m_screenWidth, m_screenHeight, m_maxLength, m_vertexCount, m_indexCount;
	bool m_shadow;
	XMFLOAT4 m_pixelColor;
};

