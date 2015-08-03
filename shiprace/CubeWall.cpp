#include "CubeWall.h"

//Movement
const float SPEED = 150;

//Scale
const float SCALE_X = 10.f;
const float SCALE_Y = 10.f;
const float SCALE_Z = 1.f;

//Position
const float POS_Z = 200.f;


CubeWall::CubeWall()
	: PrimitiveModel(PrimitiveModel::CUBE)
	, mPosZ(POS_Z)
	, mMissingSide(false)
{
	SetScale(SCALE_X, SCALE_Y, SCALE_Z);
}


CubeWall::~CubeWall()
{
}

void CubeWall::Update()
{
	//Each cube in the wall handles its own movement.
	//If it is chosen as the missing side, it does not move.

	currentPosition = GetPosition();

	mPosZ -= SPEED * gTimer->GetDeltaTime();

	if (!mMissingSide)
	{
		SetPosition(currentPosition.x, currentPosition.y, mPosZ);
	}
	
}

void CubeWall::SetActive(bool toggle)
{
	isActive = toggle;
}