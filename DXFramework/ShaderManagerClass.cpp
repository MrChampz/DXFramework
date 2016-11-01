/////////////////////////////////////////////
//	Filename: ShaderManagerClass.h
/////////////////////////////////////////////
#include "ShaderManagerClass.h"

ShaderManagerClass::ShaderManagerClass()
{
	m_ColorShader = 0;
	m_TextureShader = 0;
	m_BumMapShader = 0;
	m_SpecMapShader = 0;
	m_FogShader = 0;
	m_ClipPlaneShader = 0;
	m_LightShader = 0;
	m_ReflectionShader = 0;
	m_FontShader = 0;
	m_MiniMapShader = 0;
	m_SkyDomeShader = 0;
	m_WaterShader = 0;
	m_TerrainShader = 0;
}

ShaderManagerClass::ShaderManagerClass(const ShaderManagerClass& other)
{
}

ShaderManagerClass::~ShaderManagerClass()
{
}

bool ShaderManagerClass::Initialize(ID3D10Device* device, HWND hwnd)
{
	bool result;

	// Create the ColorShader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}

	// Initialize the ColorShader object.
	result = m_ColorShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the TextureShader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Initialize the TextureShader object.
	result = m_TextureShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the BumpMapShader object.
	m_BumMapShader = new BumpMapShaderClass;
	if (!m_BumMapShader)
	{
		return false;
	}

	// Initialize the BumpMapShader object.
	result = m_BumMapShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the SpecMapShader object.
	m_SpecMapShader = new SpecMapShaderClass;
	if (!m_SpecMapShader)
	{
		return false;
	}

	// Initialize the SpecMapShader object.
	result = m_SpecMapShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the FogShader object.
	m_FogShader = new FogShaderClass;
	if (!m_FogShader)
	{
		return false;
	}

	// Initialize the FogShader object.
	result = m_FogShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the ClipPlaneShader object.
	m_ClipPlaneShader = new ClipPlaneShaderClass;
	if (!m_ClipPlaneShader)
	{
		return false;
	}

	// Initialize the ClipPlaneShader object.
	result = m_ClipPlaneShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if (!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the reflection shader object.
	m_ReflectionShader = new ReflectionShaderClass;
	if (!m_ReflectionShader)
	{
		return false;
	}

	// Initialize the reflection shader object.
	result = m_ReflectionShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the FontShader object.
	m_FontShader = new FontShaderClass;
	if (!m_FontShader)
	{
		return false;
	}

	// Initialize the FontShader object.
	result = m_FontShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the MiniMapShader object.
	m_MiniMapShader = new MiniMapShaderClass;
	if (!m_MiniMapShader)
	{
		return false;
	}

	// Initialize the MiniMapShader object.
	result = m_MiniMapShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the skydome shader object.
	m_SkyDomeShader = new SkyDomeShaderClass;
	if (!m_SkyDomeShader)
	{
		return false;
	}

	// Initialize the skydome shader object.
	result = m_SkyDomeShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the water shader object.
	m_WaterShader = new WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

	// Initialize the water shader object.
	result = m_WaterShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if (!m_TerrainShader)
	{
		return false;
	}

	// Initialize the terrain shader object.
	result = m_TerrainShader->Initialize(device, hwnd);
	if (!result)
	{
		return false;
	}

	return true;
}

void ShaderManagerClass::Shutdown()
{
	// Release the terrain shader object.
	if (m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}

	// Release the water shader object.
	if (m_WaterShader)
	{
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	// Release the skydome shader object.
	if (m_SkyDomeShader)
	{
		m_SkyDomeShader->Shutdown();
		delete m_SkyDomeShader;
		m_SkyDomeShader = 0;
	}

	// Release the MiniMapShader object.
	if (m_MiniMapShader)
	{
		m_MiniMapShader->Shutdown();
		delete m_MiniMapShader;
		m_MiniMapShader = 0;
	}

	// Release the FontShader object.
	if (m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the ReflectionShader object.
	if (m_ReflectionShader)
	{
		m_ReflectionShader->Shutdown();
		delete m_ReflectionShader;
		m_ReflectionShader = 0;
	}

	// Release the ClipPlane object.
	if (m_ClipPlaneShader)
	{
		m_ClipPlaneShader->Shutdown();
		delete m_ClipPlaneShader;
		m_ClipPlaneShader = 0;
	}

	// Release the FogShader object.
	if (m_FogShader)
	{
		m_FogShader->Shutdown();
		delete m_FogShader;
		m_FogShader = 0;
	}

	// Release the SpecMapShader object.
	if (m_SpecMapShader)
	{
		m_SpecMapShader->Shutdown();
		delete m_SpecMapShader;
		m_SpecMapShader = 0;
	}

	// Release the BumpMapShader object.
	if (m_BumMapShader)
	{
		m_BumMapShader->Shutdown();
		delete m_BumMapShader;
		m_BumMapShader = 0;
	}

	// Release the TextureShader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the light shader object.
	if (m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the ColorShader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	return;
}

bool ShaderManagerClass::RenderColorShader(ID3D10Device* device, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	return m_ColorShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix);
}

bool ShaderManagerClass::RenderTextureShader(ID3D10Device* device, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture)
{
	return m_TextureShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
}

bool ShaderManagerClass::RenderBumpMapShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D10ShaderResourceView** textureArray, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor)
{
	return m_BumMapShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray,
		lightDirection, diffuseColor);
}

bool ShaderManagerClass::RenderSpecMapShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D10ShaderResourceView** textureArray, XMFLOAT3 lightDirection,
	XMFLOAT4 diffuseColor, XMFLOAT3 cameraPosition, XMFLOAT4 specularColor, float specularPower)
{
	return m_SpecMapShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, textureArray,
		lightDirection, diffuseColor, cameraPosition, specularColor, specularPower);
}

bool ShaderManagerClass::RenderFogShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, float fogStart, float fogEnd)
{
	return m_FogShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, fogStart, fogEnd);
}

bool ShaderManagerClass::RenderClipPlaneShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, XMFLOAT4 clipPlane)
{
	return m_ClipPlaneShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, clipPlane);
}

bool ShaderManagerClass::RenderLightShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, XMFLOAT3 cameraPosition,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
	return m_LightShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, lightDirection,
		diffuseColor, cameraPosition);
}

bool ShaderManagerClass::RenderReflectionShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, ID3D10ShaderResourceView* normalMap,
	XMFLOAT4 diffuseColor, XMFLOAT3 lightDirection, float colorTextureBrightness, XMFLOAT4 clipPlane)
{
	return m_ReflectionShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix,
		texture, normalMap, diffuseColor, lightDirection, colorTextureBrightness, clipPlane);
}

bool ShaderManagerClass::RenderFontShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix,	XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, XMFLOAT4 color)
{
	return m_FontShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, color);
}

bool ShaderManagerClass::RenderMiniMapShader(ID3D10Device* device, int indexCount,
	XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture)
{
	return m_MiniMapShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture);
}

bool ShaderManagerClass::RenderSkyDomeShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D10ShaderResourceView* cubeMap)
{
	return m_SkyDomeShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, cubeMap);
}

bool ShaderManagerClass::RenderWaterShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
	XMMATRIX projectionMatrix, XMMATRIX reflectionMatrix, ID3D10ShaderResourceView* refractionTexture,
	ID3D10ShaderResourceView* reflectionTexture, ID3D10ShaderResourceView* normalTexture, XMFLOAT3 cameraPosition,
	XMFLOAT2 normalMapTiling, float waterTranslation, float reflecRefractScale, XMFLOAT4 refractionTint, XMFLOAT3 lightDirection,
	float specularShininess)
{
	return m_WaterShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, reflectionMatrix,
		refractionTexture, reflectionTexture, normalTexture, cameraPosition, normalMapTiling, waterTranslation, reflecRefractScale,
		refractionTint, lightDirection, specularShininess);
}

bool ShaderManagerClass::RenderTerrainShader(ID3D10Device* device, int indexCount, XMMATRIX worldMatrix,
	XMMATRIX viewMatrix, XMMATRIX projectionMatrix, ID3D10ShaderResourceView* texture, ID3D10ShaderResourceView* normalMap,
	XMFLOAT3 lightDirection, XMFLOAT4 diffuseColor)
{
	return m_TerrainShader->Render(device, indexCount, worldMatrix, viewMatrix, projectionMatrix, texture, normalMap,
		lightDirection, diffuseColor);
}