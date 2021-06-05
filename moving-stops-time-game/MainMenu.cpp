#include "MainMenu.h"

MainMenu::MainMenu() {

	newGameStarted = false;
	quit = false;

	inputManager = InputManager::Instance();

	menuContainer = new GameEntity(Graphics::Instance()->SCREEN_WIDTH / 2, Graphics::Instance()->SCREEN_WIDTH / 3);

	newGameButton = new Sprite("New Game", "Roboto-Regular.ttf", 36, { 255,255,255 });
	continueGameButton = new Sprite("Continue Game", "Roboto-Regular.ttf", 36, { 255,255,255 });
	quitGameButton = new Sprite("Quit Game", "Roboto-Regular.ttf", 36, { 255,255,255 });

	cursor = new Sprite("hand-cursor.png");

	newGameButton->Parent(menuContainer);
	continueGameButton->Parent(menuContainer);
	quitGameButton->Parent(menuContainer);
	cursor->Parent(menuContainer);

	newGameButton->Position(Vector2(0.0f, -80.0f));
	continueGameButton->Position(Vector2(0.0f, 0.0f));
	quitGameButton->Position(Vector2(0.0f, 80.0f));
	cursor->Position(Vector2(-160.0f, -80.0f));
}

MainMenu::~MainMenu() {

	delete inputManager;
	inputManager = NULL;
	delete menuContainer;
	menuContainer = NULL;
	delete newGameButton;
	newGameButton = NULL;
	delete continueGameButton;
	continueGameButton = NULL;
	delete quitGameButton;
	quitGameButton = NULL;
	delete cursor;
	cursor = NULL;
}

bool MainMenu::NewGame() {
	return newGameStarted;
}

void MainMenu::Update() {

	if (IsActive()) {

		if (inputManager->KeyPressed(SDL_SCANCODE_W)) {
			if (cursor->GetPosition(GameEntity::local).y <= newGameButton->GetPosition(GameEntity::local).y) {
				cursor->Position(Vector2(-160.0f, quitGameButton->GetPosition(GameEntity::local).y));
			}
			else
				cursor->Translate(-80.0f * VEC2_UP);
		}

		if (inputManager->KeyPressed(SDL_SCANCODE_S)) {
			if (cursor->GetPosition(GameEntity::local).y >= quitGameButton->GetPosition(GameEntity::local).y) {
				cursor->Position(Vector2(-160.0f, newGameButton->GetPosition(GameEntity::local).y));
			}
			else
				cursor->Translate(80.0f * VEC2_UP);
		}

		if (inputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
			if (cursor->GetPosition(GameEntity::local).y < 0.0f) {
				//new game pressed
				Active(false);
				newGameStarted = true;
			}
			else if (cursor->GetPosition(GameEntity::local).y > 0.0f) {
				//quit game pressed
				quit = true;
			}
			else {
				//continue game pressed
				//Active(false);
			}
		}

		cursor->Update();

	}
}

void MainMenu::Render() {

	if (IsActive()) {
		newGameButton->Render();
		continueGameButton->Render();
		quitGameButton->Render();
		cursor->Render();
	}
}

bool MainMenu::Quit() {
	return quit;
}