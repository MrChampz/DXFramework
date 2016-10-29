/////////////////////////////////////////////
//	Filename: BitmapClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <DirectXMath.h>
#include <d3d10.h>
using namespace DirectX;

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "TextureClass.h"

/////////////////////////////////////////////
//	Class name: BitmapClass
/////////////////////////////////////////////
class BitmapClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool Initialize(ID3D10Device*, int, int, char*, int, int);
	void Shutdown();
	bool Render(ID3D10Device*, int, int);

	int GetIndexCount();
	ID3D10ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D10Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D10Device*, int, int);
	void RenderBuffers(ID3D10Device*);

	bool LoadTexture(ID3D10Device*, char*);
	void ReleaseTexture();

private:
	ID3D10Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;

	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
};