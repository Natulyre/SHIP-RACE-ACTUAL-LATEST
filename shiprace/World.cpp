#include "World.h"

const float OUTER_CUBE_X = 10.f;
const float OUTER_CUBE_Y = 0.f;
const float INNER_CUBE_X = 10.f;
const float INNER_CUBE_Y = -10.f;
const float MIDDLE_CUBE_X = 0.f;
const float MIDDLE_CUBE_Y = -15.f;
const float DIAGONAL_ANGLE = 15.f;
const float CUBE_Z = 200.f;

World::World()
:mCollisionChecked(false)
, mCurrentPos(0, 0, 0)
, mWallPosition(0.f, 30.f, 200.f)
, mMissingSide(0)
{
	//The tunnel and ship are created, and then the wall of cubes
	//is created. The 6th cube, cubeMeasure, is used to check the
	//location of the actual wall and is never seen on-screen.

	mTunnel = new Tunnel();
	mShip = new Ship();
	mCubeMeasure = new CubeWall();
	mLives = new Text(20, 10);
	mMermaid = new Sprite(Texture::MERMAID);
	mCubeMeasure->SetPosition(0.f, 30.f, CUBE_Z);

	//Create our 5 cube walls used as obstacles
	CreateCube(OUTER_CUBE_X, OUTER_CUBE_Y, CUBE_Z);
	CreateCube(INNER_CUBE_X, INNER_CUBE_Y, CUBE_Z, DIAGONAL_ANGLE);
	CreateCube(MIDDLE_CUBE_X, MIDDLE_CUBE_Y, CUBE_Z);
	CreateCube(-INNER_CUBE_X, INNER_CUBE_Y, CUBE_Z, DIAGONAL_ANGLE);
	CreateCube(-OUTER_CUBE_X, OUTER_CUBE_Y, CUBE_Z);

	//At the start of the game, the MissingObstacle function is called
	//to remove one cube from the wall immediately.
	ResetWorld();
}

World::~World()
{
	delete mShip;
	delete mTunnel;
	delete mCubeMeasure;
	delete mLives;
	delete mMermaid;

	//Clean up our cubewall vector.
	for (std::vector<CubeWall*>::iterator iter = mCubeWallVector.begin(); iter != mCubeWallVector.end();)
	{
		delete * iter;
		iter = mCubeWallVector.erase(iter);
	}

}

//Create a cube and automatically place it within our vector of cubewalls
void World::CreateCube(float x, float y, float z, float zRotation)
{
	CubeWall* cube = new CubeWall();
	cube->SetPosition(x, y, z);
	cube->SetRotationZ(zRotation);
	mCubeWallVector.push_back(cube);
}

//Reset the world back to its default state
void World::ResetWorld()
{
	mIsGameOver = false;
	mShip->Reset();
	MissingObstacle();
}

//Toggle the active state of every world actors
void World::SetActive(bool toggle)
{
	mShip->SetActive(toggle);
	mTunnel->SetActive(toggle);
	mCubeMeasure->SetActive(toggle);
	mLives->SetActive(toggle);
	mMermaid->SetActive(false);
//	mMermaid->SetActive(toggle);
	for each (CubeWall* c in mCubeWallVector)
	{
		c->SetActive(toggle);
	}
}

void World::Update()
{
	//As long as the player has more than one life, we'll keep on updating our walls
	UpdateWallPosition();
	mTextToDisplay = "Lives: " + mShip->GetLives();
	//mLives->SetText(mTextToDisplay.c_str());
	if (mShip->GetLives() == 0)
	{
		mIsGameOver = true;
	}
}

void World::UpdateWallPosition()
{
	//The wallPosition vector is simply the location of a cube
	//that is outside the screen and follows the real wall.
	//The collision is checked when the cubes reach the ship
	//and a new missing cube is chosen immediately after.

	mWallPosition = mCubeMeasure->GetPosition();

	if (mWallPosition.z <= 10.f && !mCollisionChecked)
	{
		CheckCollision();
		mCollisionChecked = true;
	}

	if (mWallPosition.z <= 0.f)
	{
		mCubeMeasure->SetPosZ(CUBE_Z);
		MissingObstacle();
		mCollisionChecked = false;
	}
}

void World::MissingObstacle()
{
	//Every time the cubes reach the location of the camera, a new
	//cube is randomly chose as the "hole" the ship can now go through.
	//Then, all cubes are sent to the back of the tunnel.

	mMissingSide = rand() % 5;

	for (int i = 0; i < mCubeWallVector.size(); i++)
	{
		if (i == mMissingSide)
		{
			mCurrentPos = mCubeWallVector[i]->GetPosition();
			mCubeWallVector[i]->SetMissingSide(true);
			mCubeWallVector[i]->SetPosition(mCurrentPos.x, mCurrentPos.y, CUBE_Z);
		}
		else
		{
			mCubeWallVector[i]->SetPosZ(CUBE_Z);
			mCubeWallVector[i]->SetMissingSide(false);
		}
	}
}

void World::CheckCollision()
{
	//When the cube reaches the location of the camera, this function
	//checks whether the ship is within the "safe" angle boundaries.
	// If it is, the player's rewarded with a nifty sound. If it isn't, the player loses a life.

	int currentAngle = mShip->GetShipAngle();
	bool success = false;

	switch (mMissingSide)
	{
	case 0:
		if (currentAngle >= -10.f)
		{
			success = true;
		}
		break;
	case 1:
		if (currentAngle <= -30.f && currentAngle >= -55.f)
		{
			success = true;
		}
		break;
	case 2:
		if (currentAngle <= -75.f && currentAngle >= -105.f)
		{
			success = true;
		}
		break;
	case 3:
		if (currentAngle <= -120.f && currentAngle >= -150.f)
		{
			success = true;
		}
		break;
	case 4:
		if (currentAngle <= -175.f)
		{
			success = true;
		}
		break;
	default:
		break;
	}

	success ? mShip->Success() : mShip->Hurt();

}