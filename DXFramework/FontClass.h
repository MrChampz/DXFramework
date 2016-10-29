/////////////////////////////////////////////
//	Filename: FontClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <DirectXMath.h>
#include <d3d10.h>
#include <fstream>
using namespace DirectX;
using namespace std;

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "TextureClass.h"

/////////////////////////////////////////////
//	Class name: FontClass
/////////////////////////////////////////////
class FontClass
{
private:
	struct FontType
	{
		float left, right;
		int size;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	FontClass();
	FontClass(const FontClass&);
	~FontClass();

	bool Initialize(ID3D10Device*, char*, char*, float, int);
	void Shutdown();

	ID3D10ShaderResourceView* GetTexture();
	void BuildVertexArray(void*, char*, float, float);
	int GetSentencePixelLength(char*);
	int GetFontHeight();

private:
	bool LoadFontData(char*);
	void ReleaseFontData();
	bool LoadTexture(ID3D10Device*, char*);
	void ReleaseTexture();

private:
	FontType* m_Font;
	TextureClass* m_Texture;
	float m_fontHeight;
	int m_spaceSize;
};

