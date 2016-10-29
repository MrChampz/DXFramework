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

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool RenderColorShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX);
	bool RenderTextureShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
	bool RenderBumpMapShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView**,
		XMFLOAT3, XMFLOAT4);
	bool RenderSpecMapShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView**,
		XMFLOAT3, XMFLOAT4, XMFLOAT3, XMFLOAT4, float);
	bool RenderLightShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
		XMFLOAT3, XMFLOAT3, XMFLOAT4);
	bool RenderReflectionShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, XMFLOAT4, XMFLOAT3, float, XMFLOAT4);
	bool RenderFontShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*, XMFLOAT4);
	bool RenderMiniMapShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
	bool RenderSkyDomeShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*);
	bool RenderWaterShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT2, float, float, XMFLOAT4, XMFLOAT3, float);
	bool RenderTerrainShader(ID3D11DeviceContext*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, XMFLOAT3, XMFLOAT4);

private:
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
	BumpMapShaderClass* m_BumMapShader;
	SpecMapShaderClass* m_SpecMapShader;
	LightShaderClass* m_LightShader;
	ReflectionShaderClass* m_ReflectionShader;
	FontShaderClass* m_FontShader;
	MiniMapShaderClass* m_MiniMapShader;
	SkyDomeShaderClass* m_SkyDomeShader;
	WaterShaderClass* m_WaterShader;
	TerrainShaderClass* m_TerrainShader;
};

