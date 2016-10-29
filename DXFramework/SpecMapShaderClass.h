/////////////////////////////////////////////
//	Filename: SpecMapShaderClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <d3d10.h>
#include <fstream>
using namespace DirectX;
using namespace std;

/////////////////////////////////////////////
//	Class name: SpecMapShaderClass
/////////////////////////////////////////////
class SpecMapShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

	struct LightBufferType
	{
		XMFLOAT4 diffuseColor;
		XMFLOAT4 specularColor;
		float specularPower;
		XMFLOAT3 lightDirection;
	};

	struct CameraBufferType
	{
		XMFLOAT3 cameraPosition;
		float padding;
	};

public:
	SpecMapShaderClass();
	SpecMapShaderClass(const SpecMapShaderClass&);
	~SpecMapShaderClass();

	bool Initialize(ID3D10Device*, HWND);
	void Shutdown();
	bool Render(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView**, XMFLOAT3, XMFLOAT4,
		XMFLOAT3, XMFLOAT4, float);

private:
	bool InitializeShader(ID3D10Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D10Device*, XMMATRIX, XMMATRIX, XMMATRIX, ID3D10ShaderResourceView**, XMFLOAT3, XMFLOAT4,
		XMFLOAT3, XMFLOAT4, float);
	void RenderShader(ID3D10Device*, int);

private:
	ID3D10VertexShader* m_vertexShader;
	ID3D10PixelShader* m_pixelShader;
	ID3D10InputLayout* m_layout;
	ID3D10SamplerState* m_sampleState;
	ID3D10Buffer* m_matrixBuffer;
	ID3D10Buffer* m_lightBuffer;
	ID3D10Buffer* m_cameraBuffer;
};

