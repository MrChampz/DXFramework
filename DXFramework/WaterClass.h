/////////////////////////////////////////////
//	Filename: WaterClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d11.h>
#include <DirectXMath.h>
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

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, float, float);
	void Shutdown();
	void Frame();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

	float GetWaterHeight();
	XMFLOAT2 GetNormalMapTiling();
	float GetWaterTranslation();
	float GetReflectRefractScale();
	XMFLOAT4 GetRefractionTint();
	float GetSpecularShininess();

private:
	bool InitializeBuffers(ID3D11Device*, float);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

private:
	float m_waterHeight;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	XMFLOAT2 m_normalMapTiling;
	float m_waterTranslation;
	float m_reflectRefractScale;
	XMFLOAT4 m_refractionTint;
	float m_specularShininess;
};