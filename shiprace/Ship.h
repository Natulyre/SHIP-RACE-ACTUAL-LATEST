#pragma once

#include "PrimitiveModel.h"
#include "CubeWall.h"
#include "ResourceIDs.h"

class Ship
	: PrimitiveModel
{
public:
	Ship();
	~Ship();

	void Update();
	void ShipInput();
	void ShipGravity(float angle);
	void SetActive(bool toggle);
	void Reset();
	void Hurt();
	void Success();

	void ResetObstacles();

	int GetLives(){ return mLives; }
	float GetShipAngle(){ return mShipAngleDegrees; }

private:
	const float SPEED;
	const float TUNNEL_RADIUS;
	const float DEFAULT_GRAVITY;

	int mLives;
	float mGravity;
	float mShipAngle;
	float mShipPosX;
	float mShipPosY;

	float mShipAngleDegrees;
};

