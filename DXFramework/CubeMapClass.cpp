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

bool CubeMapClass::Initialize(ID3D10Device* device, wchar_t* filename)
{
	HRESULT result;

	// Load the DDS cubemap and create the texture view
	result = CreateDDSTextureFromFileEx(device, filename, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 
		D3D11_RESOURCE_MISC_TEXTURECUBE, false, nullptr, &m_textureView, nullptr);
	if (FAILED(result))
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