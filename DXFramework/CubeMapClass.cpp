/////////////////////////////////////////////
//	Filename: CubeMapClass.cpp
/////////////////////////////////////////////
#include "CubeMapClass.h"

CubeMapClass::CubeMapClass()
{
	m_textureView = 0;
}

CubeMapClass::CubeMapClass(const CubeMapClass& other)
{
}

CubeMapClass::~CubeMapClass()
{
}

bool CubeMapClass::Initialize(ID3D10Device* device, char* filename)
{
	bool result;

	result = TGALoader::LoadCubeMap(device, "Data/SkyDome/posx.tga", "Data/SkyDome/negx.tga", "Data/SkyDome/posy.tga",
		"Data/SkyDome/negy.tga", "Data/SkyDome/posz.tga", "Data/SkyDome/negz.tga", &m_textureView);
	if (!result)
	{
		return false;
	}

	return true;
}

void CubeMapClass::Shutdown()
{
	// Release the texture view resource
	if (m_textureView)
	{
		m_textureView->Release();
		m_textureView = 0;
	}

	return;
}

ID3D10ShaderResourceView* CubeMapClass::GetCubeMap()
{
	return m_textureView;
}