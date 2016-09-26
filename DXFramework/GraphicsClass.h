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
#include "TextureShaderClass.h"
#include "BitmapClass.h"
//
#include "ModelClass.h"

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
	bool Frame();

private:
	bool Render(float);

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	//
	ModelClass* m_Model;
};