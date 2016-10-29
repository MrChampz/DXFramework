/////////////////////////////////////////////
//	Filename: TerrainCellClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d10_1.h>
#include <d3d10.h>
#include <DirectXMath.h>
using namespace DirectX;

/////////////////////////////////////////////
//	Class name: TerrainCellClass
/////////////////////////////////////////////
class TerrainCellClass
{
private:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
		float tx, ty, tz;
		float bx, by, bz;
		float r, g, b;
	};

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
		XMFLOAT3 color;
	};

	struct VectorType
	{
		float x, y, z;
	};

	struct ColorVertexType
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};

public:
	TerrainCellClass();
	TerrainCellClass(const TerrainCellClass&);
	~TerrainCellClass();

	bool Initialize(ID3D10Device*, void*, int, int, int, int, int);
	void Shutdown();
	void Render(ID3D10Device*);
	void RenderLineBuffers(ID3D10Device*);

	int GetVertexCount();
	int GetIndexCount();
	int GetLineBuffersIndexCount();
	void GetCellDimensions(float&, float&, float&, float&, float&, float&);

private:
	bool InitializeBuffers(ID3D10Device*, int, int, int, int, int, ModelType*);
	void ShutdownBuffers();
	void RenderBuffers(ID3D10Device*);
	void CalculateCellDimensions();
	bool BuildLineBuffers(ID3D10Device*);
	void ShutdownLineBuffers();

public:
	VectorType* m_vertexList;

private:
	int m_vertexCount, m_indexCount, m_lineIndexCount;
	ID3D10Buffer *m_vertexBuffer, *m_indexBuffer, *m_lineVertexBuffer, *m_lineIndexBuffer;
	float m_maxWidth, m_maxHeight, m_maxDepth, m_minWidth, m_minHeight, m_minDepth;
	float m_positionX, m_positionY, m_positionZ;
};

