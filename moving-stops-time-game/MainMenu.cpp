#include "MainMenu.h"

MainMenu::MainMenu() {

	mode = NEW;
	newGame = continueGame = quitGame = false;

	inputManager = InputManager::Instance();
	camera = Camera::Instance();

	camera->Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	menuBox = new GameEntity(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2);

	newGameButton = new Sprite("New Game", "Amatic-Regular.ttf", 100, { 0, 0, 0});
	continueGameButton = new Sprite("Continue", "Amatic-Regular.ttf", 100, { 0, 0, 0});
	quitGameButton = new Sprite("Quit", "Amatic-Regular.ttf", 100, { 0, 0, 0 });
	cursor = new Sprite("hand-cursor.png");

	newGameButton->Parent(menuBox);
	continueGameButton->Parent(menuBox);
	quitGameButton->Parent(menuBox);
	cursor->Parent(menuBox);

	newGameButton->Position(VEC2_ZERO);
	continueGameButton->Position(VEC2_ZERO);
	quitGameButton->Position(VEC2_ZERO);
	cursor->Position(VEC2_ZERO);

	cursor->Scale(2 * VEC2_ONE);

	newGameButton->Position(100 * VEC2_DOWN);
	quitGameButton->Position(100 * VEC2_UP);
	cursor->Position(200 * VEC2_LEFT + 100 * VEC2_DOWN);
}

MainMenu::~MainMenu() {

	inputManager = nullptr;

	delete menuBox;
	menuBox = nullptr;
	delete newGameButton;
	newGameButton = nullptr;
	delete continueGameButton;
	continueGameButton = nullptr;
	delete quitGameButton;
	quitGameButton = nullptr;
	delete cursor;
	cursor = nullptr;

	camera->Release();
	camera = nullptr;
}

bool MainMenu::NewGame() {

	return newGame;
}

bool MainMenu::ContinueGame() {

	return continueGame;
}

bool MainMenu::QuitGame() {

	return quitGame;
}

void MainMenu::Update() {

	if (inputManager->KeyPressed(SDL_SCANCODE_W)) {

		cursor->Translate(100 * VEC2_DOWN);

		if (cursor->GetPosition(GameEntity::local).y < newGameButton->GetPosition(GameEntity::local).y)
			cursor->Position(Vector2(cursor->GetPosition(GameEntity::local).x, quitGameButton->GetPosition(GameEntity::local).y));
	}
	else if (inputManager->KeyPressed(SDL_SCANCODE_S)) {

		cursor->Translate(100 * VEC2_UP);

		if (cursor->GetPosition(GameEntity::local).y > quitGameButton->GetPosition(GameEntity::local).y)
			cursor->Position(Vector2(cursor->GetPosition(GameEntity::local).x, newGameButton->GetPosition(GameEntity::local).y));
	}

	if (cursor->GetPosition(GameEntity::local).y < continueGameButton->GetPosition(GameEntity::local).y)
		mode = NEW;
	else if (cursor->GetPosition(GameEntity::local).y > continueGameButton->GetPosition(GameEntity::local).y)
		mode = QUIT;
	else
		mode = CONTINUE;

	if (inputManager->KeyPressed(SDL_SCANCODE_RETURN)) {

		switch (mode) {

		case NEW:

			printf("Starting new game...\n");
			newGame = true;
			break;

		case CONTINUE:

			printf("Loading game...\n");
			break;

		case QUIT:

			printf("Quit game.\n");
			quitGame = true;
			break;

		default:
			break;
		}
	}
}

void MainMenu::Render() {

	newGameButton->Render();
	continueGameButton->Render();
	quitGameButton->Render();
	cursor->Render();
}