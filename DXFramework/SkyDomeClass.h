/////////////////////////////////////////////
//	Filename: SkyDomeClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
using namespace DirectX;
using namespace std;

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "CubeMapClass.h"

/////////////////////////////////////////////
//	Class name: SkyDomeClass
/////////////////////////////////////////////
class SkyDomeClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	SkyDomeClass();
	SkyDomeClass(const SkyDomeClass&);
	~SkyDomeClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	ID3D11ShaderResourceView* GetCubeMap();
	int GetIndexCount();
	XMFLOAT4 GetApexColor();
	XMFLOAT4 GetCenterColor();

private:
	bool LoadSkyDomeModel(char*);
	void ReleaseSkyDomeModel();

	bool LoadCubeMap(ID3D11Device*, ID3D11DeviceContext*, wchar_t*);
	void ReleaseCubeMap();

	bool InitializeBuffers(ID3D11Device*);
	void ReleaseBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

private:
	CubeMapClass* m_CubeMap;
	ModelType* m_model;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer *m_vertexBuffer, * m_indexBuffer;
	XMFLOAT4 m_apexColor, m_centerColor;
};

