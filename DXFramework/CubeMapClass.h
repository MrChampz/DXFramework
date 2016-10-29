/////////////////////////////////////////////
//	Filename: CubeMapClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <DirectXMath.h>
#include "DDSTextureLoader.h"
#include <d3d10.h>
using namespace DirectX;

/////////////////////////////////////////////
//	Class name: CubeMapClass
/////////////////////////////////////////////
class CubeMapClass
{
public:
	CubeMapClass();
	CubeMapClass(const CubeMapClass&);
	~CubeMapClass();

	bool Initialize(ID3D10Device*, wchar_t*);
	void Shutdown();

	ID3D10ShaderResourceView* GetCubeMap();

private:
	ID3D10ShaderResourceView* m_textureView;
};