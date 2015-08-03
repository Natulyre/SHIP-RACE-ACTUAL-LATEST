#pragma once

#include "Component.h"
#include "World.h"
#include "Sprite.h"

enum States
{
	Starting,
	Playing,
	GameOver
};


class ShipRace :
	public Component
{
public:
	ShipRace();
	~ShipRace();

	void Update();
	void ChangeState(States newState);
	void InitScreen(Sprite* sprite);

private:

	World* mWorld;
	States mCurrentState;
	Sprite* mStartingScreen;
	Sprite* mGameOverScreen;
};

