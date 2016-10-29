/////////////////////////////////////////////
//	Filename: TextureArrayClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d11.h>
#include <stdio.h>

/////////////////////////////////////////////
//	Class name: TextureArrayClass
/////////////////////////////////////////////
class TextureArrayClass
{
private:
	struct TargaHeader
	{
		unsigned char data1[12];
		unsigned short width;
		unsigned short height;
		unsigned char bpp;
		unsigned char data2;
	};

public:
	TextureArrayClass();
	TextureArrayClass(const TextureArrayClass&);
	~TextureArrayClass();

	bool Initialize(ID3D10Device*, char*, char*, char*);
	void Shutdown();

	ID3D10ShaderResourceView** GetTextureArray();

private:
	bool LoadTarga(char*, int&, int&);

private:
	unsigned char* m_targaData;
	ID3D10Texture2D* m_texture;
	ID3D10ShaderResourceView* m_textureView[3];
};