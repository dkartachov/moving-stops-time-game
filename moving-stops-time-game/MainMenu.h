#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"

class MainMenu : public GameEntity {
public:
	MainMenu();
	~MainMenu();

	bool NewGame();

	void Update();
	void Render();
	bool Quit();
private:
	bool newGameStarted;
	bool quit;
	InputManager* inputManager;

	GameEntity* menuContainer;

	Sprite* newGameButton;
	Sprite* continueGameButton;
	Sprite* quitGameButton;

	Sprite* cursor;
};