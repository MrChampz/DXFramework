/////////////////////////////////////////////
//	Filename: ShaderManagerClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "D3DClass.h"
#include "ColorShaderClass.h"
#include "TextureShaderClass.h"
#include "BumpMapShaderClass.h"
#include "SpecMapShaderClass.h"
#include "FogShaderClass.h"
#include "ClipPlaneShaderClass.h"
#include "LightShaderClass.h"
#include "ReflectionShaderClass.h"
#include "FontShaderClass.h"
#include "MiniMapShaderClass.h"
#include "SkyDomeShaderClass.h"
#include "WaterShaderClass.h"
#include "TerrainShaderClass.h"

/////////////////////////////////////////////
//	Class name: ShaderManagerClass
/////////////////////////////////////////////
class ShaderManagerClass
{
public:
	ShaderManagerClass();
	ShaderManagerClass(const ShaderManagerClass&);
	~ShaderManagerClass();

	bool Initialize(ID3D10Device*, HWND);
	void Shutdown();

	bool RenderColorShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX);
	bool RenderTextureShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*);
	bool RenderBumpMapShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView**,
		XMFLOAT3, XMFLOAT4);
	bool RenderSpecMapShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView**,
		XMFLOAT3, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);
	bool RenderFogShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*, float, float);
	bool RenderClipPlaneShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*, XMFLOAT4);
	bool RenderLightShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*,
		XMFLOAT3, XMFLOAT3, XMFLOAT4);
	bool RenderReflectionShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*,
		ID3D10ShaderResourceView*, XMFLOAT4, XMFLOAT3, float, XMFLOAT4);
	bool RenderFontShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*, XMFLOAT4);
	bool RenderMiniMapShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*);
	bool RenderSkyDomeShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*);
	bool RenderWaterShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*,
		ID3D10ShaderResourceView*, ID3D10ShaderResourceView*, XMFLOAT3, XMFLOAT2, float, float, XMFLOAT4, XMFLOAT3, float);
	bool RenderTerrainShader(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView*,
		ID3D10ShaderResourceView*, XMFLOAT3, XMFLOAT4);

private:
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	BumpMapShaderClass* m_BumMapShader;
	SpecMapShaderClass* m_SpecMapShader;
	FogShaderClass* m_FogShader;
	ClipPlaneShaderClass* m_ClipPlaneShader;
	LightShaderClass* m_LightShader;
	ReflectionShaderClass* m_ReflectionShader;
	FontShaderClass* m_FontShader;
	MiniMapShaderClass* m_MiniMapShader;
	SkyDomeShaderClass* m_SkyDomeShader;
	WaterShaderClass* m_WaterShader;
	TerrainShaderClass* m_TerrainShader;
};

