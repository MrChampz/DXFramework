/////////////////////////////////////////////
//	Filename: ColorShaderClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d10_1.h>
#include <d3d10.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <fstream>
using namespace DirectX;
using namespace std;

/////////////////////////////////////////////
//	Class name: ColorShaderClass
/////////////////////////////////////////////
class ColorShaderClass
{
private:
	struct MatrixBufferType
	{
		XMMATRIX world;
		XMMATRIX view;
		XMMATRIX projection;
	};

public:
	ColorShaderClass();
	ColorShaderClass(const ColorShaderClass&);
	~ColorShaderClass();

	bool Initialize(ID3D10Device*, HWND);
	void Shutdown();
	bool Render(ID3D10Device*, int, XMMATRIX, XMMATRIX, XMMATRIX);

private:
	bool InitializeShader(ID3D10Device*, HWND, WCHAR*, WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool SetShaderParameters(ID3D10Device*, XMMATRIX, XMMATRIX, XMMATRIX);
	void RenderShader(ID3D10Device*, int);

private:
	ID3D10VertexShader* m_vertexShader;
	ID3D10PixelShader* m_pixelShader;
	ID3D10InputLayout* m_layout;
	ID3D10Buffer* m_matrixBuffer;
};

