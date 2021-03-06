/////////////////////////////////////////////
//	Filename: GraphicsClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <Windows.h>

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "D3DClass.h"
#include "CameraClass.h"
#include "TextClass.h"
#include "ModelClass.h"
#include "ModelListClass.h"
#include "FrustumClass.h"
#include "AlphaMapShaderClass.h"

/////////////////////////////////////////////
//	GLOBALS
/////////////////////////////////////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

/////////////////////////////////////////////
//	Class Name: GraphicsClass
/////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, float);
	bool Render();

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	TextClass* m_Text;
	ModelClass* m_Model;
	ModelListClass* m_ModelList;
	FrustumClass* m_Frustum;
	AlphaMapShaderClass* m_AlphaMapShader;
};