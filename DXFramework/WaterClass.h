/////////////////////////////////////////////
//	Filename: WaterClass.h
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
//	Class name: WaterClass
/////////////////////////////////////////////
class WaterClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	WaterClass();
	WaterClass(const WaterClass&);
	~WaterClass();

	bool Initialize(ID3D10Device*, char*, float, float);
	void Shutdown();
	void Frame();
	void Render(ID3D10Device*);

	int GetIndexCount();
	ID3D10ShaderResourceView* GetTexture();

	float GetWaterHeight();
	XMFLOAT2 GetNormalMapTiling();
	float GetWaterTranslation();
	float GetReflectRefractScale();
	XMFLOAT4 GetRefractionTint();
	float GetSpecularShininess();

private:
	bool InitializeBuffers(ID3D10Device*, float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D10Device*);

	bool LoadTexture(ID3D10Device*, char*);
	void ReleaseTexture();

private:
	float m_waterHeight;
	ID3D10Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	XMFLOAT2 m_normalMapTiling;
	float m_waterTranslation;
	float m_reflectRefractScale;
	XMFLOAT4 m_refractionTint;
	float m_specularShininess;
};