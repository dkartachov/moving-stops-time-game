#include "Player.h"

Player::Player() {

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

void Player::Jump() {

	printf("Jump!\n");
	grounded = false;
	velocity.y = -100.0f;
}

void Player::Update() {

	if (inputManager->KeyDown(SDL_SCANCODE_D))
		Translate(100.0f * timer->DeltaTime() * VEC2_RIGHT);

	if (inputManager->KeyDown(SDL_SCANCODE_A))
		Translate(100.0f * timer->DeltaTime() * VEC2_LEFT);

	if (inputManager->KeyPressed(SDL_SCANCODE_SPACE))
		Jump();

	if (!grounded) {

		velocity.y += g * timer->DeltaTime();

		//position.y += velocity.y * timer->DeltaTime() + 0.5f * g * timer->DeltaTime() * timer->DeltaTime();

		deltaY = velocity.y * timer->DeltaTime() + 0.5f * g * timer->DeltaTime() * timer->DeltaTime();
	
	}
	
	Translate(deltaY * VEC2_UP);

	printf("Player position: (%f, %f)\n", GetPosition().x, GetPosition().y);

	staticSprite->Update();
}

void Player::LateUpdate() {

	Translate(deltaY * VEC2_DOWN);
	staticSprite->Update();
	grounded = true;
}

void Player::Render() {

	if (IsActive()) {

		staticSprite->Render();
	}
}

SDL_Rect Player::GetRect() {
	return staticSprite->GetRect();
}