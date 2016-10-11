/////////////////////////////////////////////
//	Filename: MiniMapClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "BitmapClass.h"
#include "ShaderManagerClass.h"

/////////////////////////////////////////////
//	Class name: MiniMapClass
/////////////////////////////////////////////
class MiniMapClass
{
public:
	MiniMapClass();
	MiniMapClass(const MiniMapClass&);
	~MiniMapClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, int, int, float, float);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, ShaderManagerClass*, XMMATRIX, XMMATRIX, XMMATRIX);

	void PointPositionUpdate(float, float, float);
	void EnemyPositionUpdate(float, float);

private:
	int m_mapLocationX, m_mapLocationY, m_pointLocationX, m_pointLocationY, m_enemyLocationX, m_enemyLocationY;
	float m_pointRotation;
	float m_mapSizeX, m_mapSizeY, m_terrainWidth, m_terrainHeight;
	BitmapClass *m_FrameBitmap, *m_MiniMapBitmap, *m_PointBitmap, *m_EnemyBitmap;
};

