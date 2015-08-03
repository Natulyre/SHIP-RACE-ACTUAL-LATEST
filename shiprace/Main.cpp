#include "Utils.h"
#include "App.h"
#include "Engine.h"
#include "ShipRace.h"

int WINAPI _tWinMain(HINSTANCE hInstance, 
	HINSTANCE prevHInstance, 
	LPTSTR cmd, int showCmd)
{
	Engine* engine = new Engine(hInstance, "SpriteApp");
	gEngine = engine;

	engine->Init();

	ShipRace* game = new ShipRace();

	int assert = gEngine->Run();

	delete game;
	delete engine;

	return assert;
}
