/////////////////////////////////////////////
//	Filename: CubeMapClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include "DDSTextureLoader.h"
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

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, wchar_t*);
	void Shutdown();

	ID3D11ShaderResourceView* GetCubeMap();

private:
	ID3D11ShaderResourceView* m_textureView;
};