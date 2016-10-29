/////////////////////////////////////////////
//	Filename: TextureClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d10_1.h>
#include <d3d10.h>
#include <stdio.h>

/////////////////////////////////////////////
//	Class name: TextureClass
/////////////////////////////////////////////
class TextureClass
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
	TextureClass();
	TextureClass(const TextureClass&);
	~TextureClass();

	bool Initialize(ID3D10Device*, char*);
	void Shutdown();

	ID3D10ShaderResourceView* GetTexture();

private:
	bool LoadTarga(char*, int&, int&);

private:
	unsigned char* m_targaData;
	ID3D10Texture2D* m_texture;
	ID3D10ShaderResourceView* m_textureView;
};