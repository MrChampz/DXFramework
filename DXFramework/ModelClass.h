/////////////////////////////////////////////
//	Filename: ModelClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d10_1.h>
#include <d3d10.h>
#include <DirectXMath.h>
#include <fstream>
using namespace DirectX;
using namespace std;

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "TextureArrayClass.h"

/////////////////////////////////////////////
//	Class name: ModelClass
/////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
	};

	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VectorType
	{
		float x, y, z;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	bool Initialize(ID3D10Device*, char*, char*, char*, char*);
	void Shutdown();
	void Render(ID3D10Device*);

	int GetIndexCount();
	ID3D10ShaderResourceView** GetTextureArray();

private:
	bool InitializeBuffers(ID3D10Device*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D10Device*);

	bool LoadTextures(ID3D10Device*, char*, char*, char*);
	void ReleaseTextures();

	bool LoadModel(char*);
	void ReleaseModel();

	void CalculateModelVectors();
	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);
	void CalculateNormal(VectorType, VectorType, VectorType&);

private:
	ID3D10Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureArrayClass* m_TextureArray;
	ModelType* m_model;
};

