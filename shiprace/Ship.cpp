#include "Ship.h"

//Movement-related
const float LEFTMOST = -190.f;
const float RIGHTMOST = 10.f;
const float MIDDLE = -90.f;
const float GRAVITY_COEFF = 3.f;

//Position
const float SHIP_POS_Z = 0.f;

//Player variables
const int DEFAULT_LIVES = 3;

Ship::Ship()
: PrimitiveModel(PrimitiveModel::CONE)
, SPEED(3.f)
, TUNNEL_RADIUS(7.5f)
, mShipAngle(0.f)
, DEFAULT_GRAVITY(0.01f)
, mGravity(DEFAULT_GRAVITY)
{
	Reset();
}

Ship::~Ship()
{
}

void Ship::Update()
{
	ShipInput();
}

//Reset our player back to its default value
void Ship::Reset()
{
	mLives = DEFAULT_LIVES;
}

//Remove a life from the player and play a sad sound
void Ship::Hurt()
{
	AudioSys->play2D(Sounds->Get(Sound::Hurt));
	mLives -= 1;
}

//Reward the player with a nice tune
void Ship::Success()
{
	AudioSys->play2D(Sounds->Get(Sound::Success));
}

void Ship::ShipInput()
{
	//The shipAngleDegrees variable is the one used for measuring purposes
	//since the angle in radians is much harder to work with.
	mShipAngleDegrees = mShipAngle * 180 / D3DX_PI;

	//Ship movement in the screen. Gravity is reset each time the throttle is used.
	if ((gDInput->keyDown(DIK_RIGHT) || gDInput->keyDown(DIK_D))  && mShipAngleDegrees <= RIGHTMOST)
	{
		mShipAngle += SPEED * gTimer->GetDeltaTime();
		mGravity = DEFAULT_GRAVITY;

	}
	else if ((gDInput->keyDown(DIK_LEFT) || gDInput->keyDown(DIK_A)) && mShipAngleDegrees >= LEFTMOST)
	{
		mShipAngle -= SPEED * gTimer->GetDeltaTime();
		mGravity = DEFAULT_GRAVITY;
	}

	//Calling the gravity function to influence ship movement.
	ShipGravity(mShipAngleDegrees);

	//Calculating the vector between the middle of the tunnel and where the ship needs to be.
	mShipPosX = TUNNEL_RADIUS * cos(mShipAngle);
	mShipPosY = TUNNEL_RADIUS * sin(mShipAngle);

	//Setting position of the ship after calculating the vector and gravity.
	SetPosition(mShipPosX, mShipPosY, SHIP_POS_Z);
}
	

void Ship::ShipGravity(float angle)
{
	//Gravity is in effect if the throttle is not used.
	bool throttle = (gDInput->keyDown(DIK_RIGHT) || gDInput->keyDown(DIK_LEFT));

	if (!throttle)
	{
		//Gravity affects the ship if it is not exactly at the bottom of the tunnel.
		mGravity += GRAVITY_COEFF * gTimer->GetDeltaTime();

		if (angle > MIDDLE)
		{
			mShipAngle -= mGravity * gTimer->GetDeltaTime();
		}
		else if (angle < MIDDLE)
		{
			mShipAngle += mGravity * gTimer->GetDeltaTime();
		}
	}
}

void Ship::SetActive(bool toggle)
{
	isActive = toggle;
}