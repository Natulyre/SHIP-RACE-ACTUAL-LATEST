#pragma once
#include "PrimitiveModel.h"
class CubeWall :
	public PrimitiveModel
{
public:
	CubeWall();
	~CubeWall();

	void Update();
	
	void SetMissingSide(bool side){ mMissingSide = side; }
	void SetPosZ(float position) { mPosZ = position; }
	void SetActive(bool toggle);

private:

	D3DXVECTOR3 currentPosition;

	float mPosZ;
	bool mMissingSide;
};