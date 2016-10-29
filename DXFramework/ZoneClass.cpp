/////////////////////////////////////////////
//	Filename: ZoneClass.cpp
/////////////////////////////////////////////
#include "ZoneClass.h"

ZoneClass::ZoneClass()
{
	m_UserInterface = 0;
	m_Camera = 0;
	m_Light = 0;
	m_Position = 0;
	m_Frustum = 0;
	m_RefractionTexture = 0;
	m_ReflectionTexture = 0;
	m_SkyDome = 0;
	m_Water = 0;
	m_Terrain = 0;
	m_Model = 0;
}

ZoneClass::ZoneClass(const ZoneClass& other)
{
}

ZoneClass::~ZoneClass()
{
}

bool ZoneClass::Initialize(D3DClass* Direct3D, HWND hwnd, int screenWidth, int screenHeight, float screenDepth, float screenNear)
{
	bool result;

	// Create the UserInterface object
	m_UserInterface = new UserInterfaceClass;
	if (!m_UserInterface)
	{
		return false;
	}

	// Initialize the UserInterface object
	result = m_UserInterface->Initialize(Direct3D, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the UserInterface object", L"Error", MB_OK);
		return false;
	}

	// Create the Camera object
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera and build the matrices needed for rendering
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	m_Camera->Render();
	m_Camera->RenderBaseViewMatrix();

	// Create the light object
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Initialize the light object
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.5f, -0.75f, 0.25f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(16.0f);

	// Create the Position object
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation
	m_Position->SetPosition(20.0f, 5.0f, 20.0f);
	m_Position->SetRotation(0.0f, 222.013f, 0.0f);

	// Create the Frustum object
	m_Frustum = new FrustumClass;
	if (!m_Frustum)
	{
		return false;
	}

	// Initialize the Frustum object
	m_Frustum->Initialize(screenDepth);

	// Create the refraction render to texture object.
	m_RefractionTexture = new RenderTextureClass;
	if (!m_RefractionTexture)
	{
		return false;
	}

	// Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(Direct3D->GetDevice(), screenWidth, screenHeight, screenDepth, screenNear);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection render to texture object.
	m_ReflectionTexture = new RenderTextureClass;
	if (!m_ReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(Direct3D->GetDevice(), screenWidth, screenHeight, screenDepth, screenNear);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the skydome object
	m_SkyDome = new SkyDomeClass;
	if (!m_SkyDome)
	{
		return false;
	}

	// Initialize the skydome object
	result = m_SkyDome->Initialize(Direct3D->GetDevice());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the SkyDome object", L"Error", MB_OK);
		return false;
	}

	// Create the Water object
	m_Water = new WaterClass;
	if (!m_Water)
	{
		return false;
	}

	// Initialize the Water object
	result = m_Water->Initialize(Direct3D->GetDevice(), "Data/Water_normal.tga", 40.0f, 800.0f);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Water object", L"Error", MB_OK);
		return false;
	}

	// Create the Terrain object
	m_Terrain = new TerrainClass;
	if (!m_Terrain)
	{
		return false;
	}

	// Initialize the Terrain object
	result = m_Terrain->Initialize(Direct3D->GetDevice(), "Data/Maps/Map03/Map03.map");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Terrain object", L"Error", MB_OK);
		return false;
	}

	// Create the Model object
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}

	// Initialize the Model object
	result = m_Model->Initialize(Direct3D->GetDevice(), "Data/Cube.vin", "Data/Tile_diff.tga", "Data/Tile_norm.tga", "Data/Tile_spec.tga");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Model object", L"Error", MB_OK);
		return false;
	}

	// Define the position of the cube model
	m_modelPosX = 40.0f;
	m_modelPosZ = 40.0f;
	m_Terrain->GetHeightAtPosition(m_modelPosX, m_modelPosZ, m_modelPosY);
	m_modelPosY += 5.0f;

	// Set the UI to display by default
	m_displayUI = true;

	// Set wire frame rendering initially to enabled
	m_wireFrame = false;

	// Set the rendering of cell lines initially to enabled.
	m_cellLines = false;

	// Set the user locked to the terrain height for movement
	m_heightLocked = true;

	return true;
}

void ZoneClass::Shutdown()
{
	// Release the Model object
	if (m_Model)
	{
		m_Model->Shutdown();
		delete[] m_Model;
		m_Model = 0;
	}

	// Release the Terrain object.
	if (m_Terrain)
	{
		m_Terrain->Shutdown();
		delete m_Terrain;
		m_Terrain = 0;
	}

	// Release the water object.
	if (m_Water)
	{
		m_Water->Shutdown();
		delete m_Water;
		m_Water = 0;
	}

	// Release the skydome object.
	if (m_SkyDome)
	{
		m_SkyDome->Shutdown();
		delete m_SkyDome;
		m_SkyDome = 0;
	}

	// Release the reflection render to texture object.
	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	// Release the refraction render to texture object.
	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}

	// Release the Frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the Position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the light object.
	if (m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the Camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the UserInterface object.
	if (m_UserInterface)
	{
		m_UserInterface->Shutdown();
		delete m_UserInterface;
		m_UserInterface = 0;
	}

	return;
}

bool ZoneClass::Frame(D3DClass* Direct3D, InputClass* Input, ShaderManagerClass* ShaderManager,
	TextureManagerClass* TextureManager, float frameTime, int fps)
{
	bool result, foundHeight;
	float posX, posY, posZ, rotX, rotY, rotZ, height;

	// Do the frame input processing
	HandleMovementInput(Input, frameTime);

	// Get the view point position/rotation
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Do the frame processing for the UserInterface
	result = m_UserInterface->Frame(Direct3D->GetDevice(), fps, posX, posY, posZ, rotX, rotY, rotZ,
		m_modelPosX, m_modelPosZ);
	if (!result)
	{
		return false;
	}

	// Do the Terrain frame processing
	m_Terrain->Frame();

	// If the height is locked to the terrain then position the camera on top of it.
	if (m_heightLocked)
	{
		// Get the height of the triangle that is directly underneath the given camera position.
		foundHeight = m_Terrain->GetHeightAtPosition(posX, posZ, height);
		if (foundHeight)
		{
			// If there was a triangle under the camera then position the camera just above it by one meter.
			m_Position->SetPosition(posX, height + 1.0f, posZ);
			m_Camera->SetPosition(posX, height + 1.0f, posZ);
		}
	}

	// Render the graphics
	result = Render(Direct3D, ShaderManager, TextureManager);
	if (!result)
	{
		return false;
	}

	return true;
}

void ZoneClass::HandleMovementInput(InputClass* Input, float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position
	m_Position->SetFrameTime(frameTime);

	// Handle the input.
	keyDown = Input->IsLeftPressed();
	m_Position->TurnLeft(keyDown);

	keyDown = Input->IsRightPressed();
	m_Position->TurnRight(keyDown);

	keyDown = Input->IsUpPressed();
	m_Position->MoveForward(keyDown);

	keyDown = Input->IsDownPressed();
	m_Position->MoveBackward(keyDown);

	keyDown = Input->IsAPressed();
	m_Position->MoveUpward(keyDown);

	keyDown = Input->IsZPressed();
	m_Position->MoveDownward(keyDown);

	keyDown = Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);

	keyDown = Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	// Determine if the user interface should be displayed or not.
	if (Input->IsF1Toggled())
	{
		m_displayUI = !m_displayUI;
	}

	// Determine if the terrain should be rendered in wireframe or not.
	if (Input->IsF2Toggled())
	{
		m_wireFrame = !m_wireFrame;
	}

	// Determine if we should render the lines around each terrain cell.
	if (Input->IsF3Toggled())
	{
		m_cellLines = !m_cellLines;
	}

	// Determine if we should be locked to the terrain height when we move around or not.
	if (Input->IsF4Toggled())
	{
		m_heightLocked = !m_heightLocked;
	}

	return;
}

void ZoneClass::RenderRefractionToTexture(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager)
{
	bool result;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	XMFLOAT4 clipPlane;
	int i;

	// Setup a clipping plane based on the height of the water to clip everything above it to create a refraction.
	clipPlane = XMFLOAT4(0.0f, -1.0f, 0.0f, m_Water->GetWaterHeight() + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(Direct3D->GetDevice());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(Direct3D->GetDevice(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);

	// Construct the Frustum
	m_Frustum->ConstructFrustum(projectionMatrix, viewMatrix);

	// Render the terrain cells (and cell lines if needed).
	for (i = 0; i < m_Terrain->GetCellCount(); i++)
	{
		// Render each terrain cell if it is visible only.
		result = m_Terrain->RenderCell(Direct3D->GetDevice(), i, m_Frustum);
		if (result)
		{
			// Render the cell buffers using the terrain shader.
			result = ShaderManager->RenderTerrainShader(Direct3D->GetDevice(), m_Terrain->GetCellIndexCount(i),
				worldMatrix, viewMatrix, projectionMatrix, TextureManager->GetTexture(0), TextureManager->GetTexture(1),
				m_Light->GetDirection(), m_Light->GetDiffuseColor());
		}
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	Direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	Direct3D->ResetViewport();

	return;
}

void ZoneClass::RenderReflectionToTexture(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager)
{
	bool result;
	XMMATRIX worldMatrix, reflectionViewMatrix, projectionMatrix;
	XMFLOAT4 clipPlane;
	XMFLOAT3 cameraPosition;
	int i;

	// Setup a clipping plane based on the height of the water to clip everything below it
	clipPlane = XMFLOAT4(0.0f, 1.0f, 0.0f, -m_Water->GetWaterHeight());

	// Set the render target to be the refraction render to texture.
	m_ReflectionTexture->SetRenderTarget(Direct3D->GetDevice());

	// Clear the refraction render to texture.
	m_ReflectionTexture->ClearRenderTarget(Direct3D->GetDevice(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	// Get the camera reflection view matrix instead of the normal view matrix.
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the world and projection matrices from the d3d object.
	Direct3D->GetWorldMatrix(worldMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);

	// Get the position of the camera.
	cameraPosition = m_Camera->GetPosition();

	// Invert the Y coordinate of the camera around the water plane height for the reflected camera position.
	cameraPosition.y = -cameraPosition.y + (m_Water->GetWaterHeight() * 2.0f);

	// Turn off back face culling and turn off the Z buffer
	Direct3D->TurnOffCulling();
	Direct3D->TurnZBufferOff();

	// Translate the sky dome to be centered around the camera position
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(Direct3D->GetDevice());
	result = ShaderManager->RenderSkyDomeShader(Direct3D->GetDevice(), m_SkyDome->GetIndexCount(), worldMatrix,
		reflectionViewMatrix, projectionMatrix, m_SkyDome->GetCubeMap());

	// Reset the world matrix
	Direct3D->GetWorldMatrix(worldMatrix);

	// Turn the Z buffer and back face culling off
	Direct3D->TurnOnCulling();
	Direct3D->TurnZBufferOn();

	
	// Construct the Frustum
	m_Frustum->ConstructFrustum(projectionMatrix, reflectionViewMatrix);

	// Render the terrain cells (and cell lines if needed).
	for (i = 0; i < m_Terrain->GetCellCount(); i++)
	{
		// Render all terrain cells
		result = m_Terrain->RenderAllCells(Direct3D->GetDevice(), i);

		if (result)
		{
			// Render the cell buffers using the terrain shader.
			result = ShaderManager->RenderReflectionShader(Direct3D->GetDevice(), m_Terrain->GetCellIndexCount(i),
				worldMatrix, reflectionViewMatrix, projectionMatrix, TextureManager->GetTexture(0), TextureManager->GetTexture(1),
				m_Light->GetDiffuseColor(), m_Light->GetDirection(), 2.0f, clipPlane);
		}
	}

	worldMatrix = XMMatrixTranslation(m_modelPosX, m_modelPosY, m_modelPosZ);

	m_Model->Render(Direct3D->GetDevice());
	result = ShaderManager->RenderTextureShader(Direct3D->GetDevice(), m_Model->GetIndexCount(), worldMatrix, reflectionViewMatrix,
		projectionMatrix, *m_Model->GetTextureArray());

	Direct3D->GetWorldMatrix(worldMatrix);

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	Direct3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	Direct3D->ResetViewport();

	return;
}

bool ZoneClass::Render(D3DClass* Direct3D, ShaderManagerClass* ShaderManager, TextureManagerClass* TextureManager)
{
	bool result;
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, baseViewMatrix, reflectionViewMatrix;;
	XMFLOAT3 cameraPosition;
	int i;

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the reflection matrix based on the camera's position and the height of the water.
	m_Camera->RenderReflection(m_Water->GetWaterHeight());

	// Get the world, view, and projection matrices from the camera and d3d objects.
	Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	Direct3D->GetProjectionMatrix(projectionMatrix);
	Direct3D->GetOrthoMatrix(orthoMatrix);
	m_Camera->GetBaseViewMatrix(baseViewMatrix);
	m_Camera->GetReflectionViewMatrix(reflectionViewMatrix);

	// Get the position of the camera
	cameraPosition = m_Camera->GetPosition();

	// Construct the Frustum
	m_Frustum->ConstructFrustum(projectionMatrix, viewMatrix);

	// Clear the buffers to begin the scene.
	Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Turn off back face culling and turn off the Z buffer
	Direct3D->TurnOffCulling();
	Direct3D->TurnZBufferOff();

	// Translate the sky dome to be centered around the camera position
	worldMatrix = XMMatrixTranslation(cameraPosition.x, cameraPosition.y, cameraPosition.z);

	// Render the sky dome using the sky dome shader.
	m_SkyDome->Render(Direct3D->GetDevice());
	result = ShaderManager->RenderSkyDomeShader(Direct3D->GetDevice(), m_SkyDome->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_SkyDome->GetCubeMap());
	if (!result)
	{
		return false;
	}

	// Reset the world matrix
	Direct3D->GetWorldMatrix(worldMatrix);

	// Turn the Z buffer and back face culling off
	Direct3D->TurnOnCulling();
	Direct3D->TurnZBufferOn();

	// Turn on wire frame rendering of the terrain if needed.
	if (m_wireFrame)
	{
		Direct3D->EnableWireframe();
	}

	// Render the terrain cells (and cell lines if needed).
	for (i = 0; i < m_Terrain->GetCellCount(); i++)
	{
		// Render each terrain cell if it is visible only.
		result = m_Terrain->RenderCell(Direct3D->GetDevice(), i, m_Frustum);
		if (result)
		{
			// Render the cell buffers using the terrain shader.
			result = ShaderManager->RenderTerrainShader(Direct3D->GetDevice(), m_Terrain->GetCellIndexCount(i),
				worldMatrix, viewMatrix, projectionMatrix, TextureManager->GetTexture(0), TextureManager->GetTexture(1),
				m_Light->GetDirection(), m_Light->GetDiffuseColor());
			if (!result)
			{
				return false;
			}

			// If needed then render the bounding box around this terrain cell using the color shader. 
			if (m_cellLines)
			{
				m_Terrain->RenderCellLines(Direct3D->GetDevice(), i);
				ShaderManager->RenderColorShader(Direct3D->GetDevice(), m_Terrain->GetCellLinesIndexCount(i),
					worldMatrix, viewMatrix, projectionMatrix);
				if (!result)
				{
					return false;
				}
			}
		}
	}

	/**
	 *	
	 */

	worldMatrix = XMMatrixTranslation(m_modelPosX, m_modelPosY, m_modelPosZ);

	m_Model->Render(Direct3D->GetDevice());
	result = ShaderManager->RenderSpecMapShader(Direct3D->GetDevice(), m_Model->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_Model->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	//

	// Reset the world matrix.
	Direct3D->GetWorldMatrix(worldMatrix);

	// Turn off wire frame rendering of the terrain if it was on.
	if (m_wireFrame)
	{
		Direct3D->DisableWireframe();
	}

	// Update the render counts in the UI.
	result = m_UserInterface->UpdateRenderCounts(Direct3D->GetDevice(), m_Terrain->GetRenderCount(),
		m_Terrain->GetCellsDrawn(), m_Terrain->GetCellsCulled());
	if (!result)
	{
		return false;
	}

	// Render the user interface.
	if (m_displayUI)
	{
		result = m_UserInterface->Render(Direct3D, ShaderManager, worldMatrix, baseViewMatrix, orthoMatrix);
		if (!result)
		{
			return false;
		}
	}

	// Present the rendered scene to the screen.
	Direct3D->EndScene();

	return true;
}
