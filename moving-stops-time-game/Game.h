#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "SceneOne.h"
#include "MainMenu.h"

class Game {
public:
	Game();
	~Game();

	void EarlyUpdate();
	void Update();
	void LateUpdate();

	void Run();
	void Render();

	void Quit();
private:
	const int FRAME_RATE = 60;
	bool quit;

	Timer* timer;
	Graphics* graphics;
	SDL_Event events;
	AssetManager* assetManager;
	InputManager* inputManager;
	AudioManager* audioManager;
	Collision* collision;
	Camera* camera;

	SceneOne* sceneOne;
	MainMenu* mainMenu;
};