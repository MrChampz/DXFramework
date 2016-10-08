/////////////////////////////////////////////
//	Filename: ApplicationClass.cpp
/////////////////////////////////////////////
#include "ApplicationClass.h"

ApplicationClass::ApplicationClass()
{
	m_Input = 0;
	m_Direct3D = 0;
	m_Timer = 0;
	m_Fps = 0;
	m_ShaderManager = 0;
	m_TextureManager = 0;
	m_Zone = 0;
}

ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}

ApplicationClass::~ApplicationClass()
{
}

bool ApplicationClass::Initialize(HINSTANCE hInstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the Input object
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the Input object
	result = m_Input->Initialize(hInstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Input object", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the ShaderManager object
	m_ShaderManager = new ShaderManagerClass;
	if (!m_ShaderManager)
	{
		return false;
	}

	// Initialize the ShaderManager object
	result = m_ShaderManager->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ShaderManager object", L"Error", MB_OK);
		return false;
	}

	// Create the TextureManager object
	m_TextureManager = new TextureManagerClass;
	if (!m_TextureManager)
	{
		return false;
	}

	// Initialize the TextureManager object
	result = m_TextureManager->Initialize(10);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the TextureManager object", L"Error", MB_OK);
		return false;
	}

	// Load textures into TextureManager
	result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(),
		"Data/Maps/Dirt_diff.tga", 0);
	if (!result)
	{
		return false;
	}

	result = m_TextureManager->LoadTexture(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(),
		"Data/Maps/Dirt_normal.tga", 1);
	if (!result)
	{
		return false;
	}

	// Create the timer object
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the Timer object
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Timer object", L"Error", MB_OK);
		return false;
	}

	// Create the Fps object
	m_Fps = new FpsClass;
	if (!m_Fps)
	{
		return false;
	}

	// Initialize the Fps object
	m_Fps->Initialize();

	// Create the Zone object
	m_Zone = new ZoneClass;
	if (!m_Zone)
	{
		return false;
	}

	// Initialize the zone object
	result = m_Zone->Initialize(m_Direct3D, hwnd, screenWidth, screenHeight, SCREEN_DEPTH);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Zone object", L"Error", MB_OK);
		return false;
	}

	return true;
}

void ApplicationClass::Shutdown()
{
	// Release the Zone object
	if (m_Zone)
	{
		m_Zone->Shutdown();
		delete m_Zone;
		m_Zone = 0;
	}

	// Release the Fps object
	if (m_Fps)
	{
		delete m_Fps;
		m_Fps = 0;
	}

	// Release the Timer object
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the TextureManager object
	if (m_TextureManager)
	{
		m_TextureManager->Shutdown();
		delete[] m_TextureManager;
		m_TextureManager = 0;
	}

	// Release the ShaderManager object
	if (m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the Direct3D object
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the Input object
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}

bool ApplicationClass::Frame()
{
	bool result;

	// Update the system stats
	m_Fps->Frame();
	m_Timer->Frame();

	// Do the input frame processing
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the zone frame processing
	result = m_Zone->Frame(m_Direct3D, m_Input, m_ShaderManager, m_TextureManager, m_Timer->GetTime(), m_Fps->GetFps());
	if (!result)
	{
		return false;
	}

	return result;
}