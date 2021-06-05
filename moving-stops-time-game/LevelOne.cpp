#include "LevelOne.h"

LevelOne::LevelOne() {

	inputManager = InputManager::Instance();

	sprite = new Sprite("hand-cursor.png");
	sprite->Position(Vector2(Graphics::Instance()->SCREEN_WIDTH / 2, Graphics::Instance()->SCREEN_HEIGHT / 2));
	sprite->Rotate(90.0f);
	sprite->Scale(2 * VEC2_ONE);
}

LevelOne::~LevelOne() {
	delete sprite;
	sprite = NULL;
}

void LevelOne::Update(GameEntity* pauseMenu, GameEntity* player) {

	if (IsActive()) {

		if (!pauseMenu->IsActive())
			player->Update();

		if (inputManager->KeyPressed(SDL_SCANCODE_ESCAPE)) {

			pauseMenu->Active(true);
		}
	}
}

void LevelOne::Render(GameEntity* player) {
	
	if (IsActive()) {

		player->Render();
		sprite->Render();
	}
}