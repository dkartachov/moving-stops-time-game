#include "Player.h"

Player::Player() {

	inputManager = InputManager::Instance();
	timer = Timer::Instance();

	Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	velocity = VEC2_ZERO;

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
	Translate(2 * VEC2_DOWN);
	velocity.y = -100.0f;
}

void Player::Update() {

	if (inputManager->KeyDown(SDL_SCANCODE_D))
		Translate(100.0f * timer->DeltaTime() * VEC2_RIGHT);

	if (inputManager->KeyDown(SDL_SCANCODE_A))
		Translate(100.0f * timer->DeltaTime() * VEC2_LEFT);

	if (inputManager->KeyPressed(SDL_SCANCODE_SPACE))
		Jump();

	position = GetPosition();

	velocity.y += g * timer->DeltaTime();
	deltaY = velocity.y * timer->DeltaTime() + 0.5f * g * timer->DeltaTime() * timer->DeltaTime();

	Translate(deltaY * VEC2_UP);

	printf("Position: (%f, %f)\n", position.x, position.y);
	printf("Velocity: (%f, %f)\n", velocity.x, velocity.y);
}

void Player::LateUpdate() {

	Translate(deltaY * VEC2_DOWN);
}

void Player::Render() {

	if (IsActive()) {

		staticSprite->Render();
	}
}

SDL_Rect Player::GetRect() {
	return staticSprite->GetRect();
}