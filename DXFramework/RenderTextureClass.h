/////////////////////////////////////////////
//	Filename: RenderTextureClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <DirectXMath.h>
#include <d3d10.h>
using namespace DirectX;

/////////////////////////////////////////////
//	Class name: RenderTextureClass
/////////////////////////////////////////////
class RenderTextureClass
{
public:
	RenderTextureClass();
	RenderTextureClass(const RenderTextureClass&);
	~RenderTextureClass();

	bool Initialize(ID3D10Device*, int, int, float, float);
	void Shutdown();

	void SetRenderTarget(ID3D10Device*);
	void ClearRenderTarget(ID3D10Device*, float, float, float, float);
	ID3D10ShaderResourceView* GetShaderResourceView();
	void GetProjectionMatrix(XMMATRIX&);
	void GetOrthoMatrix(XMMATRIX&);

private:
	ID3D10Texture2D* m_renderTargetTexture;
	ID3D10RenderTargetView* m_renderTargetView;
	ID3D10ShaderResourceView* m_shaderResourceView;
	ID3D10Texture2D* m_depthStencilBuffer;
	ID3D10DepthStencilView* m_depthStencilView;
	D3D10_VIEWPORT m_viewport;
	XMMATRIX m_projectionMatrix;
	XMMATRIX m_orthoMatrix;
};

