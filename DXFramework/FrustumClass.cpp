/////////////////////////////////////////////
//	Filename: FrustumClass.cpp
/////////////////////////////////////////////
#include "FrustumClass.h"

FrustumClass::FrustumClass()
{
}

FrustumClass::FrustumClass(const FrustumClass& other)
{
}

FrustumClass::~FrustumClass()
{
}

void FrustumClass::ConstructFrustum(float screenDepth, XMMATRIX projectionMatrix, XMMATRIX viewMatrix)
{
	float zMinimum, r;
	XMMATRIX matrix;

	// 
	XMFLOAT4X4 pMatrix;
	XMFLOAT4X4 vMatrix;
	XMFLOAT4X4 mMatrix;

	// Transform the matrices into Float4x4s for more flexibility
	XMStoreFloat4x4(&pMatrix, projectionMatrix);
	XMStoreFloat4x4(&vMatrix, viewMatrix);

	// Calculate the minimum Z distance in the frustum
	zMinimum = -pMatrix._43 / pMatrix._33;
	r = screenDepth / (screenDepth - zMinimum);
	pMatrix._33 = r;
	pMatrix._43 = -r * zMinimum;

	// Create the frustum matrix from the view matrix and updated projection matrix
	//matrix = XMMatrixMultiply(viewMatrix, projectionMatrix);
	matrix = XMMatrixMultiply(XMLoadFloat4x4(&vMatrix), XMLoadFloat4x4(&pMatrix));
	
	// Transform the final matrice into Float4x4 for more flexibility
	XMStoreFloat4x4(&mMatrix, matrix);

	// Calculate near plane of frustum.
	m_planes[0].x = mMatrix._14 + mMatrix._13;
	m_planes[0].y = mMatrix._24 + mMatrix._23;
	m_planes[0].z = mMatrix._34 + mMatrix._33;
	m_planes[0].w = mMatrix._44 + mMatrix._43;
	XMStoreFloat4(&m_planes[0], XMLoadFloat4(&m_planes[0]));

	// Calculate far plane of frustum.
	m_planes[1].x = mMatrix._14 - mMatrix._13;
	m_planes[1].y = mMatrix._24 - mMatrix._23;
	m_planes[1].z = mMatrix._34 - mMatrix._33;
	m_planes[1].w = mMatrix._44 - mMatrix._43;
	XMStoreFloat4(&m_planes[1], XMLoadFloat4(&m_planes[1]));

	// Calculate left plane of frustum.
	m_planes[2].x = mMatrix._14 + mMatrix._11;
	m_planes[2].y = mMatrix._24 + mMatrix._21;
	m_planes[2].z = mMatrix._34 + mMatrix._31;
	m_planes[2].w = mMatrix._44 + mMatrix._41;
	XMStoreFloat4(&m_planes[2], XMLoadFloat4(&m_planes[2]));

	// Calculate right plane of frustum.
	m_planes[3].x = mMatrix._14 - mMatrix._11;
	m_planes[3].y = mMatrix._24 - mMatrix._21;
	m_planes[3].z = mMatrix._34 - mMatrix._31;
	m_planes[3].w = mMatrix._44 - mMatrix._41;
	XMStoreFloat4(&m_planes[3], XMLoadFloat4(&m_planes[3]));

	// Calculate top plane of frustum.
	m_planes[4].x = mMatrix._14 - mMatrix._12;
	m_planes[4].y = mMatrix._24 - mMatrix._22;
	m_planes[4].z = mMatrix._34 - mMatrix._32;
	m_planes[4].w = mMatrix._44 - mMatrix._42;
	XMStoreFloat4(&m_planes[4], XMLoadFloat4(&m_planes[4]));

	// Calculate bottom plane of frustum.
	m_planes[5].x = mMatrix._14 + mMatrix._12;
	m_planes[5].y = mMatrix._24 + mMatrix._22;
	m_planes[5].z = mMatrix._34 + mMatrix._32;
	m_planes[5].w = mMatrix._44 + mMatrix._42;
	XMStoreFloat4(&m_planes[5], XMLoadFloat4(&m_planes[5]));

	return;
}

bool FrustumClass::CheckPoint(float x, float y, float z)
{
	int i;

	// Check if the point is inside all six planes of the view frustum
	for (i = 0; i < 6; i++)
	{
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3(x, y, z)))) < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if any one point of the cube is in the view frustum.
	for (i = 0; i<6; i++)
	{
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - radius), (yCenter - radius), (zCenter - radius))))) >= 0.0f)
		{											  
			continue;								  
		}											  
													  
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + radius), (yCenter - radius), (zCenter - radius))))) >= 0.0f)
		{											  
			continue;								  
		}											  
													  
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - radius), (yCenter + radius), (zCenter - radius))))) >= 0.0f)
		{											  
			continue;								  
		}											  
													  
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + radius), (yCenter + radius), (zCenter - radius))))) >= 0.0f)
		{											  
			continue;								  
		}											  
													  
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - radius), (yCenter - radius), (zCenter + radius))))) >= 0.0f)
		{											  
			continue;								  
		}											  
													  
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + radius), (yCenter - radius), (zCenter + radius))))) >= 0.0f)
		{											  
			continue;								  
		}											  
													  
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - radius), (yCenter + radius), (zCenter + radius))))) >= 0.0f)
		{											  
			continue;								  
		}											  
													  
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + radius), (yCenter + radius), (zCenter + radius))))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}

bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	int i;


	// Check if the radius of the sphere is inside the view frustum.
	for (i = 0; i<6; i++)
	{
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3(xCenter, yCenter, zCenter)))) < -radius)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	int i;


	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for (i = 0; i<6; i++)
	{
		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - xSize), (yCenter - ySize), (zCenter - zSize))))) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + xSize), (yCenter - ySize), (zCenter - zSize))))) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - xSize), (yCenter + ySize), (zCenter - zSize))))) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - xSize), (yCenter - ySize), (zCenter + zSize))))) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + xSize), (yCenter + ySize), (zCenter - zSize))))) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + xSize), (yCenter - ySize), (zCenter + zSize))))) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter - xSize), (yCenter + ySize), (zCenter + zSize))))) >= 0.0f)
		{
			continue;
		}

		if (XMVectorGetX(XMPlaneDotCoord(XMLoadFloat4(&m_planes[i]), XMLoadFloat3(&XMFLOAT3((xCenter + xSize), (yCenter + ySize), (zCenter + zSize))))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
}