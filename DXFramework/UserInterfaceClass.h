/////////////////////////////////////////////
//	Filename: UserInterfaceClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "TextClass.h"
#include "MiniMapClass.h"

/////////////////////////////////////////////
//	Class name: UserInterfaceClass
/////////////////////////////////////////////
class UserInterfaceClass
{
public:
	UserInterfaceClass();
	UserInterfaceClass(const UserInterfaceClass&);
	~UserInterfaceClass();

	bool Initialize(D3DClass*, int, int);
	void Shutdown();

	bool Frame(ID3D10Device*, int, float, float, float, float, float, float, float, float);
	bool Render(D3DClass*, ShaderManagerClass*, XMMATRIX, XMMATRIX, XMMATRIX);

	bool UpdateRenderCounts(ID3D10Device*, int, int, int);

private:
	bool UpdateFpsString(ID3D10Device*, int);
	bool UpdatePositionStrings(ID3D10Device*, float, float, float, float, float, float);

private:
	FontClass* m_Font1;
	TextClass *m_FpsString, *m_VideoStrings, *m_PositionStrings, *m_RenderCountStrings;
	MiniMapClass* m_MiniMap;
	int m_previousFps;
	int m_previousPosition[6];
};

