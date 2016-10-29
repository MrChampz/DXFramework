/////////////////////////////////////////////
//	Filename: ZoneClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "D3DClass.h"
#include "InputClass.h"
#include "ShaderManagerClass.h"
#include "TextureManagerClass.h"
#include "TimerClass.h"
#include "UserInterfaceClass.h"
#include "CameraClass.h"
#include "LightClass.h"
#include "PositionClass.h"
#include "FrustumClass.h"
#include "RenderTextureClass.h"
#include "SkyDomeClass.h"
#include "WaterClass.h"
#include "TerrainClass.h"
#include "ModelClass.h"

/////////////////////////////////////////////
//	Class name: ZoneClass
/////////////////////////////////////////////
class ZoneClass
{
public:
	ZoneClass();
	ZoneClass(const ZoneClass&);
	~ZoneClass();

	bool Initialize(D3DClass*, HWND, int, int, float, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, ShaderManagerClass*, TextureManagerClass*, float, int);

private:
	void HandleMovementInput(InputClass*, float);
	void RenderRefractionToTexture(D3DClass*, ShaderManagerClass*, TextureManagerClass*);
	void RenderReflectionToTexture(D3DClass*, ShaderManagerClass*, TextureManagerClass*);
	bool Render(D3DClass*, ShaderManagerClass*, TextureManagerClass*);

private:
	UserInterfaceClass* m_UserInterface;
	CameraClass* m_Camera;
	LightClass* m_Light;
	PositionClass* m_Position;
	FrustumClass* m_Frustum;
	RenderTextureClass *m_RefractionTexture, *m_ReflectionTexture;
	SkyDomeClass* m_SkyDome;
	WaterClass* m_Water;
	TerrainClass* m_Terrain;
	bool m_displayUI, m_wireFrame, m_cellLines, m_heightLocked;
	ModelClass* m_Model;
	float m_modelPosX, m_modelPosY, m_modelPosZ;
};

