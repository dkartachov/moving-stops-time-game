#include "Player.h"

Player::Player() {

	moving = false;
	grounded = false;

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

void Player::Grounded(bool state) {
	grounded = state;
}

bool Player::IsMoving() {
	return moving;
}

void Player::Jump() {

	printf("Jump!\n");
	grounded = false;
	velocity.y = -200.0f;
}

void Player::Update() {

	if (velocity.x > 0.0f || velocity.x < 0.0f)
		moving = true;
	else
		moving = false;

	if (inputManager->KeyDown(SDL_SCANCODE_D))
		velocity.x = 200.0f * timer->DeltaTime();
	else if (inputManager->KeyDown(SDL_SCANCODE_A))
		velocity.x = -200.0f * timer->DeltaTime();
	else
		velocity.x = 0.0f;

	Translate(velocity.x * VEC2_RIGHT);
		
	if (inputManager->KeyPressed(SDL_SCANCODE_SPACE))
		Jump();

	if (!grounded) {

		velocity.y += g * timer->DeltaTime();

		//position.y += velocity.y * timer->DeltaTime() + 0.5f * g * timer->DeltaTime() * timer->DeltaTime();

		deltaY = velocity.y * timer->DeltaTime() + 0.5f * g * timer->DeltaTime() * timer->DeltaTime();
	}

	Translate(deltaY * VEC2_UP);

	printf("Player position: (%f, %f)\n", GetPosition().x, GetPosition().y);
	printf("Player velocity: (%f, %f)\n", velocity.x, velocity.y);

	staticSprite->Update();
}

void Player::LateUpdate() {

	Translate(deltaY * VEC2_DOWN);
	staticSprite->Update();
	velocity.y = 0.0f;
}

void Player::Render() {

	if (IsActive()) {

		staticSprite->Render();
	}
}

SDL_Rect Player::GetRect() {
	return staticSprite->GetRect();
}