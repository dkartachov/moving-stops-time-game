#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Player.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "LevelOne.h"

class Game {
public:
	static Game* Instance();
	static void Release();

	Game();
	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Run();
	void Render();

	void Quit();
private:
	static Game* instance;
	const int FRAME_RATE = 140;
	bool quit;

	Timer* timer;
	Graphics* graphics;
	SDL_Event events;
	AssetManager* assetManager;
	InputManager* inputManager;
	AudioManager* audioManager;

	MainMenu* mainMenu;
	PauseMenu* pauseMenu;

	LevelOne* levelOne;

	Player* player;
};