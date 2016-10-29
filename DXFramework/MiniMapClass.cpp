/////////////////////////////////////////////
//	Filename: MiniMapClass.cpp
/////////////////////////////////////////////
#include "MiniMapClass.h"

MiniMapClass::MiniMapClass()
{
	m_FrameBitmap = 0;
	m_MiniMapBitmap = 0;
	m_PointBitmap = 0;
	m_EnemyBitmap = 0;
}

MiniMapClass::MiniMapClass(const MiniMapClass& other)
{
}

MiniMapClass::~MiniMapClass()
{
}

bool MiniMapClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int screenWidth, int screenHeight,
	float terrainWidth, float terrainHeight)
{
	bool result;

	// Set initial rotation
	m_pointRotation = 0.0f;

	// Set the size of the mini-map minus the borders
	m_mapSizeX = 150.0f;
	m_mapSizeY = 150.0f;

	// Initialize the location of the mini-map on the screen
	m_mapLocationX = screenWidth - (int)m_mapSizeX - 20;
	m_mapLocationY = 20;

	// Store the terrain size
	m_terrainWidth = terrainWidth;
	m_terrainHeight = terrainHeight;

	// Create the frame bitmap object
	m_FrameBitmap = new BitmapClass;
	if (!m_FrameBitmap)
	{
		return false;
	}

	// Initialize the frame bitmap object
	result = m_FrameBitmap->Initialize(device, deviceContext, screenWidth, screenHeight, "Data/MiniMap/Frame.tga",
		170, 170);
	if (!result)
	{
		return false;
	}

	// Create the mini-map bitmap object
	m_MiniMapBitmap = new BitmapClass;
	if (!m_MiniMapBitmap)
	{
		return false;
	}

	// Initialize the mini-map bitmap object
	result = m_MiniMapBitmap->Initialize(device, deviceContext, screenWidth, screenHeight, "Data/Maps/Map03/MiniMap.tga",
		150, 150);
	if (!result)
	{
		return false;
	}

	// Create the enemy bitmap object
	m_EnemyBitmap = new BitmapClass;
	if (!m_EnemyBitmap)
	{
		return false;
	}

	// Initialize the enemy bitmap object
	result = m_EnemyBitmap->Initialize(device, deviceContext, screenWidth, screenHeight, "Data/MiniMap/Enemy.tga",
		11, 11);
	if (!result)
	{
		return false;
	}

	// Create the point bitmap object
	m_PointBitmap = new BitmapClass;
	if (!m_PointBitmap)
	{
		return false;
	}

	// Initialize the point bitmap object
	result = m_PointBitmap->Initialize(device, deviceContext, screenWidth, screenHeight, "Data/MiniMap/Point.tga",
		11, 11);
	if (!result)
	{
		return false;
	}

	return true;
}

void MiniMapClass::Shutdown()
{
	// Release the point bitmap object
	if (m_PointBitmap)
	{
		m_PointBitmap->Shutdown();
		delete[] m_PointBitmap;
		m_PointBitmap = 0;
	}

	// Release the enemy bitmap object
	if (m_EnemyBitmap)
	{
		m_EnemyBitmap->Shutdown();
		delete[] m_EnemyBitmap;
		m_EnemyBitmap = 0;
	}

	// Release the mini-map bitmap object
	if (m_MiniMapBitmap)
	{
		m_MiniMapBitmap->Shutdown();
		delete[] m_MiniMapBitmap;
		m_MiniMapBitmap = 0;
	}

	// Release the frame bitmap object
	if (m_FrameBitmap)
	{
		m_FrameBitmap->Shutdown();
		delete[] m_FrameBitmap;
		m_FrameBitmap = 0;
	}

	return;
}

bool MiniMapClass::Render(ID3D11DeviceContext* deviceContext, ShaderManagerClass* ShaderManager, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX orthoMatrix)
{
	bool result;

	// Put the frame bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_FrameBitmap->Render(deviceContext, (m_mapLocationX - 10), (m_mapLocationY - 10));
	if (!result)
	{
		return false;
	}

	// Render the frame bitmap using the texture shader.
	result = ShaderManager->RenderMiniMapShader(deviceContext, m_FrameBitmap->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, m_FrameBitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Put the mini-map bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_MiniMapBitmap->Render(deviceContext, m_mapLocationX, m_mapLocationY);
	if (!result)
	{
		return false;
	}

	// Render the mini-map bitmap using the texture shader.
	result = ShaderManager->RenderTextureShader(deviceContext, m_MiniMapBitmap->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, m_MiniMapBitmap->GetTexture());
	if (!result)
	{
		return false;
	}
	
	// Put the enemy bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_EnemyBitmap->Render(deviceContext, m_enemyLocationX, m_enemyLocationY);
	if (!result)
	{
		return false;
	}

	// Render the enemy bitmap using the texture shader.
	result = ShaderManager->RenderMiniMapShader(deviceContext, m_EnemyBitmap->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, m_EnemyBitmap->GetTexture());
	if (!result)
	{
		return false;
	}

	// Put the point bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = m_PointBitmap->Render(deviceContext, m_pointLocationX, m_pointLocationY);
	if (!result)
	{
		return false;
	}

	// Render the point bitmap using the texture shader.
	result = ShaderManager->RenderMiniMapShader(deviceContext, m_PointBitmap->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, m_PointBitmap->GetTexture());
	if (!result)
	{
		return false;
	}
	
	return true;
}

void MiniMapClass::PointPositionUpdate(float positionX, float positionZ, float rotation)
{
	float percentX, percentY;

	// Ensure the point does not leave the minimap borders even if the camera goes past the terrain borders.
	if (positionX < 30)
	{
		positionX = 30;
	}

	if (positionZ < 30)
	{
		positionZ = 30;
	}

	if (positionX >= m_terrainWidth - 30)
	{
		positionX = m_terrainWidth - 30;
	}

	if (positionZ >= m_terrainHeight - 30)
	{
		positionZ = m_terrainHeight - 30;
	}

	// Calculate the position of the camera on the minimap in terms of percentage.
	percentX = positionX / m_terrainWidth;
	percentY = 1.0f - (positionZ / m_terrainHeight);

	// Determine the pixel location of the point on the mini-map.
	m_pointLocationX = (m_mapLocationX) + (int)(percentX * m_mapSizeX);
	m_pointLocationY = (m_mapLocationY) + (int)(percentY * m_mapSizeY);

	// Subtract one from the location to center the point on the mini-map according to the 11x11 point pixel image size.
	m_pointLocationX = m_pointLocationX - 5;
	m_pointLocationY = m_pointLocationY - 5;

	// Store the rotation
	m_pointRotation = rotation;

	return;
}

void MiniMapClass::EnemyPositionUpdate(float positionX, float positionZ)
{
	float percentX, percentY;

	// Ensure the enemy indicator does not leave the minimap borders even if the enemy goes past the terrain borders.
	if (positionX < 30)
	{
		positionX = 30;
	}

	if (positionZ < 30)
	{
		positionZ = 30;
	}

	if (positionX >= m_terrainWidth - 30)
	{
		positionX = m_terrainWidth - 30;
	}

	if (positionZ >= m_terrainHeight - 30)
	{
		positionZ = m_terrainHeight - 30;
	}

	// Calculate the position of the enemy on the minimap in terms of percentage.
	percentX = positionX / m_terrainWidth;
	percentY = 1.0f - (positionZ / m_terrainHeight);

	// Determine the pixel location of the indicator on the mini-map.
	m_enemyLocationX = (m_mapLocationX)+(int)(percentX * m_mapSizeX);
	m_enemyLocationY = (m_mapLocationY)+(int)(percentY * m_mapSizeY);

	// Subtract one from the location to center the indicator on the mini-map
	// according to the 11x11 indicator pixel image size.
	m_enemyLocationX = m_enemyLocationX - 5;
	m_enemyLocationY = m_enemyLocationY - 5;

	return;
}