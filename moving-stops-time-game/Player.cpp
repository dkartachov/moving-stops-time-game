#include "Player.h"

Player::Player() {

	inputManager = InputManager::Instance();
	timer = Timer::Instance();

	Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	staticSprite = new Sprite("hand-cursor.png");
	staticSprite->Parent(this);
	staticSprite->Position(VEC2_ZERO);
}

Player::~Player() {

	delete inputManager;
	inputManager = NULL;
}

void Player::Jump() {

	printf("Jump!\n");


}

void Player::Update() {

	if (inputManager->KeyDown(SDL_SCANCODE_D))
		Translate(100.0f * timer->DeltaTime() * VEC2_RIGHT);

	if (inputManager->KeyDown(SDL_SCANCODE_A))
		Translate(100.0f * timer->DeltaTime() * VEC2_LEFT);

	if (inputManager->KeyPressed(SDL_SCANCODE_SPACE))
		Jump();

	Translate(100.0f * timer->DeltaTime() * VEC2_UP);
}

void Player::Render() {

	if (IsActive()) {

		staticSprite->Render();
	}
}

SDL_Rect Player::GetRect() {
	return staticSprite->GetRect();
}