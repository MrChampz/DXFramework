/////////////////////////////////////////////
//	Filename: TextureClass.cpp
/////////////////////////////////////////////
#include "TextureClass.h"

TextureClass::TextureClass()
{
	m_textureView = 0;
}

TextureClass::TextureClass(const TextureClass& other)
{
}

TextureClass::~TextureClass()
{
}

bool TextureClass::Initialize(ID3D10Device* device, char* filename)
{
	bool result;

	result = TGALoader::LoadTexture(device, filename, &m_textureView);
	if (!result)
	{
		return false;
	}

	return true;
}

void TextureClass::Shutdown()
{
	// Release the texture view resource
	if (m_textureView)
	{
		m_textureView->Release();
		m_textureView = 0;
	}

	return;
}

ID3D10ShaderResourceView* TextureClass::GetTexture()
{
	return m_textureView;
}