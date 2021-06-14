#pragma once
#include "Sprite.h"
#include "InputManager.h"

class MainMenu {
public:
	enum MODE { NEW = 0, CONTINUE, QUIT };
public:
	MainMenu();
	~MainMenu();

	bool NewGame();
	bool ContinueGame();
	bool QuitGame();

	void Update();
	void Render();
	
private:
	MODE mode;
	bool newGame, continueGame, quitGame;

	InputManager* inputManager;

	GameEntity* menuBox;
	Sprite* newGameButton;
	Sprite* continueGameButton;
	Sprite* quitGameButton;
	Sprite* cursor;
};