/////////////////////////////////////////////
//	Filename: ModelListClass.h
/////////////////////////////////////////////
#pragma once

/////////////////////////////////////////////
//	INCLUDES
/////////////////////////////////////////////
#include <DirectXMath.h>
#include <stdlib.h>
#include <time.h>
using namespace DirectX;

/////////////////////////////////////////////
//	Filename: ModelListClass
/////////////////////////////////////////////
class ModelListClass
{
private:
	struct ModelInfoType
	{
		XMFLOAT4 color;
		float positionX, positionY, positionZ;
	};

public:
	ModelListClass();
	ModelListClass(const ModelListClass&);
	~ModelListClass();

	bool Initialize(int);
	void Shutdown();

	int GetModelCount();
	void GetData(int, float&, float&, float&, XMFLOAT4&);

private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;
};

