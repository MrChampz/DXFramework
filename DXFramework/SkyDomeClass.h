/////////////////////////////////////////////
//	Filename: SkyDomeClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <DirectXMath.h>
#include <d3d10.h>
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

	bool Initialize(ID3D10Device*);
	void Shutdown();
	void Render(ID3D10Device*);

	ID3D10ShaderResourceView* GetCubeMap();
	int GetIndexCount();
	XMFLOAT4 GetApexColor();
	XMFLOAT4 GetCenterColor();

private:
	bool LoadSkyDomeModel(char*);
	void ReleaseSkyDomeModel();

	bool LoadCubeMap(ID3D10Device*, wchar_t*);
	void ReleaseCubeMap();

	bool InitializeBuffers(ID3D10Device*);
	void ReleaseBuffers();
	void RenderBuffers(ID3D10Device*);

private:
	CubeMapClass* m_CubeMap;
	ModelType* m_model;
	int m_vertexCount, m_indexCount;
	ID3D10Buffer *m_vertexBuffer, * m_indexBuffer;
	XMFLOAT4 m_apexColor, m_centerColor;
};

