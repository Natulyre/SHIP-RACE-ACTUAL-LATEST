#pragma once

#include "ResourceIDs.h"
#include "Component.h"
#include "Ship.h"
#include "Tunnel.h"
#include "CubeWall.h"

class World :
	public Component
{
public:
	World();
	~World();

	void Update();
	void ResetWorld();
	void SetActive(bool toggle);
	bool GetIsGameOver()	{ return mIsGameOver; }

	void CreateCube(float x, float y, float z, float zRotation = 0.f);

	void MissingObstacle();
	void CheckCollision();

	void UpdateWallPosition();

private:
	bool mIsGameOver;

	Tunnel* mTunnel;
	Ship* mShip;

	CubeWall* mCubeMeasure;

	std::vector <CubeWall*> mCubeWallVector;

	D3DXVECTOR3 mWallPosition;
	D3DXVECTOR3 mCurrentPos;

	bool mCollisionChecked;
	int mMissingSide;
};

