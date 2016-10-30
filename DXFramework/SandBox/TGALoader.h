/////////////////////////////////////////////
//	Filename: TGALoader.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d11.h>
#include <d3d10_1.h>
#include <d3d10.h>
#include <stdio.h>

/////////////////////////////////////////////
//	Class name: TGALoader
/////////////////////////////////////////////
class TGALoader
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
	static bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*, ID3D11ShaderResourceView**);
	static bool LoadCubeMap(ID3D11Device*, ID3D11DeviceContext*, char*, char*, char*, char*, char*, char*,
		ID3D11ShaderResourceView**);
																		  
	static bool LoadTexture(ID3D10Device*, char*, ID3D10ShaderResourceView**);
	static bool LoadCubeMap(ID3D10Device*, char*, char*, char*, char*, char*, char*, ID3D10ShaderResourceView**);

private:
	static unsigned char* LoadTarga(char*, int&, int&);
};