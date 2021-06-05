#include "Player.h"

Player::Player() {

	inputManager = InputManager::Instance();
	timer = Timer::Instance();

	player = new GameEntity(100, 700);
	staticSprite = new Sprite("hand-cursor.png");
	staticSprite->Parent(player);
	staticSprite->Position(VEC2_ZERO);
}

Player::~Player() {
	delete inputManager;
	inputManager = NULL;
}

void Player::Update() {

	if (inputManager->KeyDown(SDL_SCANCODE_D))
		player->Translate(100.0f * timer->DeltaTime() * VEC2_RIGHT);

	if (inputManager->KeyDown(SDL_SCANCODE_A))
		player->Translate(100.0f * timer->DeltaTime() * VEC2_LEFT);

	if (inputManager->KeyPressed(SDL_SCANCODE_SPACE)) {
		printf("Jump!\n");
	}
}

void Player::Render() {

	if (IsActive()) {

		staticSprite->Render();
	}
}