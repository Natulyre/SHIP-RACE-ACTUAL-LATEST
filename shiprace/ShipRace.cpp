#include "ShipRace.h"
#include "ResourceIDs.h"

//Camera values for the sprite/game switch
const float SPRITE_CAMERA_Z = 750.f;
const float GAME_CAMERA_Z = -20.f;

//Sprite display values
const float SPRITE_POSITION = 500.f;
const float SPRITE_ROTATION = 180.f;

ShipRace::ShipRace()
{
	//Load our screens
	Textures->LoadTexture(Texture::TITLE_SCREEN, "TitleScreen.png");
	Textures->LoadTexture(Texture::GAMEOVER_SCREEN, "GameOver.png");
	Textures->LoadTexture(Texture::MERMAID, "Mermaid.jpg");

	//Load our music
	Sounds->LoadSound(Sound::Game, "Wave Ocean.mp3");
	Sounds->LoadSound(Sound::Intro, "Sandbox.mp3");
	Sounds->LoadSound(Sound::Defeat, "Dark Places.mp3");

	//Load our sounds
	Sounds->LoadSound(Sound::Hurt, "Splash.wav");
	Sounds->LoadSound(Sound::Success, "Success.wav");
	Sounds->LoadSound(Sound::Button, "Button.wav");

	//Create our world
	mWorld = new World();

	//And our game screens
	mStartingScreen = new Sprite(Texture::TITLE_SCREEN);
	mGameOverScreen = new Sprite(Texture::GAMEOVER_SCREEN);
	InitScreen(mStartingScreen);
	InitScreen(mGameOverScreen);
	
	//And our text
	mStart = new Text(35,15);
	mStart->SetText("Press Space/Enter to follow the mermaid's call.");
	mStart->SetColor(0, 0, 0);
	mStart->SetFlashing(true);
	mGameOver = new Text(50,20);
	mGameOver->SetText("You've failed to reach the mermaid...");
	mGameOver->SetColor(255, 0, 0);
	mGameOver->SetHeight(-150);
	mEnd = new Text(30,10);
	mEnd->SetText("Press Space/Enter to go back to the main menu or R to retry.");
	mEnd->SetFlashing(true);
	mEnd->SetColor(0, 0, 0);
	mEnd->SetHeight(150);

	//The random generator is initialized.
	srand(time(0));

	ChangeState(States::Starting);

}

ShipRace::~ShipRace()
{
	delete mWorld;
	delete mStartingScreen;
	delete mGameOverScreen;
	delete mStart;
	delete mGameOver;
	delete mEnd;
}

//Initialize a sprite's position to be correctly displayed in front of the camera
void ShipRace::InitScreen(Sprite* sprite)
{
	sprite->SetRotationDeg(0, 0, SPRITE_ROTATION);
	sprite->SetPosition(SPRITE_POSITION, SPRITE_POSITION);
}


//Update the game states accordingly, and handle the input for state changes.
void ShipRace::Update()
{
	switch (mCurrentState)
	{
	case Starting:
		if ((gDInput->keyPressed(DIKEYBOARD_SPACE) || gDInput->keyPressed(DIKEYBOARD_RETURN)))
		{
			ChangeState(Playing);
			AudioSys->play2D(Sounds->Get(Sound::Button));
		}
		break;
	case Playing:
		if (mWorld->GetIsGameOver())
		{
			ChangeState(GameOver);
		}
		break;
	case GameOver:
		if (gDInput->keyPressed(DIKEYBOARD_R))
		{
			ChangeState(Playing);
			AudioSys->play2D(Sounds->Get(Sound::Button));
		}
		if ((gDInput->keyPressed(DIKEYBOARD_SPACE) || gDInput->keyPressed(DIKEYBOARD_RETURN)))
		{
			ChangeState(Starting);
			AudioSys->play2D(Sounds->Get(Sound::Button));
		}
		break;
	}
}

//Change game state, will activate/deactive appropriate thingies accordingly
void ShipRace::ChangeState(States newState)
{
	switch (newState)
	{
	case Starting:
		AudioSys->stopAllSounds();
		AudioSys->play2D(Sounds->Get(Sound::Intro));
		gEngine->GetCamera()->SetCamPos(D3DXVECTOR3(0, 1, SPRITE_CAMERA_Z));
		mStart->SetActive(true);
		mEnd->SetActive(false);
		mGameOver->SetActive(false);
		mStartingScreen->SetActive(true);
		mGameOverScreen->SetActive(false);
		mWorld->SetActive(false);
		break;
	case Playing:
		AudioSys->stopAllSounds();
		AudioSys->play2D(Sounds->Get(Sound::Game));
		gEngine->GetCamera()->SetCamPos(D3DXVECTOR3(0, 1, GAME_CAMERA_Z));
		mStart->SetActive(false);
		mEnd->SetActive(false);
		mGameOver->SetActive(false);
		mStartingScreen->SetActive(false);
		mGameOverScreen->SetActive(false);
		mWorld->SetActive(true);
		mWorld->ResetWorld();
		break;
	case GameOver:
		AudioSys->stopAllSounds();
		AudioSys->play2D(Sounds->Get(Sound::Defeat));
		gEngine->GetCamera()->SetCamPos(D3DXVECTOR3(0, 1, SPRITE_CAMERA_Z));
		mStart->SetActive(false);
		mEnd->SetActive(true);
		mGameOver->SetActive(true);
		mStartingScreen->SetActive(false);
		mGameOverScreen->SetActive(true);
		mWorld->SetActive(false);
		break;
	}
	mCurrentState = newState;
}


