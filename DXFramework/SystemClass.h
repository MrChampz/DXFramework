/////////////////////////////////////////////
//	Filename: SystemClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
// PRE-PROCESSING DIRECTIVES
/////////////////////////////////////////////
#define WIN32_LEAN_AND_MEAN

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <Windows.h>

/////////////////////////////////////////////
//	MY INCLUDES
/////////////////////////////////////////////
#include "InputClass.h"
#include "GraphicsClass.h"
#include "SoundClass.h"
#include "FpsClass.h"
#include "CpuClass.h"
#include "TimerClass.h"

/////////////////////////////////////////////
//	Class Name: SystemClass
/////////////////////////////////////////////
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hInstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;
	SoundClass* m_Sound;
	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	TimerClass* m_Timer;
};

/////////////////////////////////////////////
//	FUNCTION PROTOTYPES
/////////////////////////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

/////////////////////////////////////////////
//	GLOBALS
/////////////////////////////////////////////
static SystemClass* ApplicationHandle = 0;