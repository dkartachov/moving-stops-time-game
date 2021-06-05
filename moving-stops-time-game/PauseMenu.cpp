#include "PauseMenu.h"

PauseMenu::PauseMenu() {

	menu = false;
	quit = false;

	inputManager = InputManager::Instance();

	menuContainer = new GameEntity(Graphics::Instance()->SCREEN_WIDTH / 2, Graphics::Instance()->SCREEN_HEIGHT / 2);
	resumeGame = new Sprite("Resume", "Roboto-Regular.ttf", 36, { 255,255,255 });
	returnMainMenu = new Sprite("Main Menu", "Roboto-Regular.ttf", 36, { 255,255,255 });
	quitGame = new Sprite("Quit", "Roboto-Regular.ttf", 36, { 255,255,255 });

	cursor = new Sprite("hand-cursor.png");

	resumeGame->Parent(menuContainer);
	returnMainMenu->Parent(menuContainer);
	quitGame->Parent(menuContainer);
	cursor->Parent(menuContainer);

	resumeGame->Position(Vector2(0.0f, -80.0f));
	returnMainMenu->Position(Vector2(0.0f, 0.0f));
	quitGame->Position(Vector2(0.0f, 80.0f));
	cursor->Position(Vector2(-140.0f, -80.0f));
}

PauseMenu::~PauseMenu() {
	delete inputManager;
	inputManager = NULL;
	delete menuContainer;
	menuContainer = NULL;
	delete resumeGame;
	resumeGame = NULL;
	delete returnMainMenu;
	returnMainMenu = NULL;
	delete quitGame;
	quitGame = NULL;
	delete cursor;
	cursor = NULL;
}

void PauseMenu::Update(GameEntity* mainMenu) {

	if (IsActive()) {

		if (inputManager->KeyPressed(SDL_SCANCODE_W)) {
			if (cursor->GetPosition(GameEntity::local).y <= resumeGame->GetPosition(GameEntity::local).y) {
				cursor->Position(Vector2(-160.0f, quitGame->GetPosition(GameEntity::local).y));
			}
			else
				cursor->Translate(-80.0f * VEC2_UP);
		}

		if (inputManager->KeyPressed(SDL_SCANCODE_S)) {
			if (cursor->GetPosition(GameEntity::local).y >= quitGame->GetPosition(GameEntity::local).y) {
				cursor->Position(Vector2(-160.0f, resumeGame->GetPosition(GameEntity::local).y));
			}
			else
				cursor->Translate(80.0f * VEC2_UP);
		}

		if (inputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
			if (cursor->GetPosition(GameEntity::local).y < 0.0f) {
				//resume pressed
				printf("resume game\n");
				Active(false);
			}
			else if (cursor->GetPosition(GameEntity::local).y > 0.0f) {
				//quit pressed
				printf("quit game\n");
				Active(false);
				quit = true;
			}
			else {
				//main menu pressed
				printf("main menu\n");
				Active(false);
				mainMenu->Active(true);
			}
		}

		cursor->Update();
	
	}
}

void PauseMenu::Render() {

	if (IsActive()) {

		resumeGame->Render();
		returnMainMenu->Render();
		quitGame->Render();
		cursor->Render();
	}
}

bool PauseMenu::MainMenu() {
	return menu;
}

bool PauseMenu::Quit() {
	return quit;
}