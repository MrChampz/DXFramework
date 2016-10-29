/////////////////////////////////////////////
//	Filename: GraphicsClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	LINKING
/////////////////////////////////////////////
#pragma comment(lib, "d3d10.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <d3d10_1.h>
#include <d3d10.h>
#include <DirectXMath.h>
using namespace DirectX;

/////////////////////////////////////////////
//	Class Name: D3DClass
/////////////////////////////////////////////
class D3DClass
{
public:
	D3DClass();
	D3DClass(const D3DClass&);
	~D3DClass();

	bool Initialize(int, int, bool, HWND, bool, float, float);
	void Shutdown();

	void BeginScene(float, float, float, float);
	void EndScene();

	ID3D10Device* GetDevice();

	void GetProjectionMatrix(XMMATRIX&);
	void GetWorldMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

	void GetVideoCardInfo(char*, int&);

	ID3D10DepthStencilView* GetDepthStencilView();
	void SetBackBufferRenderTarget();
	void ResetViewport();

	void TurnZBufferOn();
	void TurnZBufferOff();

	void EnableAlphaBlending();
	void DisableAlphaBlending();

	void TurnOnCulling();
	void TurnOffCulling();

	void EnableWireframe();
	void DisableWireframe();

private:
	bool m_vsync_enabled;
	int m_videoCardMemory;
	char m_videoCardDescription[128];
	IDXGISwapChain* m_swapChain;
	ID3D10Device* m_device;
	ID3D10RenderTargetView* m_renderTargetView;
	ID3D10Texture2D* m_depthStencilBuffer;
	ID3D10DepthStencilState* m_depthStencilState;
	ID3D10DepthStencilState* m_depthDisabledStencilState;
	ID3D10DepthStencilView* m_depthStencilView;
	ID3D10RasterizerState* m_rasterState;
	ID3D10RasterizerState* m_rasterStateNoCulling;
	ID3D10RasterizerState* m_rasterStateWireframe;
	ID3D10BlendState* m_alphaEnableBlendingState;
	ID3D10BlendState* m_alphaDisableBlendingState;
	D3D10_VIEWPORT m_viewport;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_worldMatrix;
	XMMATRIX m_orthoMatrix;
};