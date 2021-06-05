#pragma once
//#include "MainMenu.h"
#include "Sprite.h"
#include "InputManager.h"

class PauseMenu : public GameEntity {
public:
	PauseMenu();
	~PauseMenu();

	void Update(GameEntity* mainMenu);
	void Render();

	bool MainMenu();
	bool Quit();
private:
	bool menu, quit;

	InputManager* inputManager;

	GameEntity* menuContainer;

	Sprite* resumeGame;
	Sprite* returnMainMenu;
	Sprite* quitGame;

	Sprite* cursor;
};