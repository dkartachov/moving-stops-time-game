#include "Player.h"

Player::Player(Collision* coll) {

	collision = coll;

	moving = false;
	grounded = false;

	inputManager = InputManager::Instance();
	timer = Timer::Instance();

	Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	velocity = VEC2_ZERO;

	idleAnim = new AnimatedSprite("idle.png", 0, 0, 80, 80, 18, 1);
	idleAnim->Parent(this);
	idleAnim->Position(VEC2_ZERO);

	runAnim = new AnimatedSprite("run.png", 0, 0, 80, 80, 24, 1);
	runAnim->Parent(this);
	runAnim->Position(VEC2_ZERO);
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

	grounded = false;
	velocity.y = -200.0f;
}

void Player::PlayAnim(ANIM anim) {

	currentAnim = anim;

	switch (anim) {
	case IDLE:

		idleAnim->Play();
		break;

	case RUNNING:

		runAnim->Play();
		break;

	default:
		break;
	}
}

void Player::Update() {

	prevPos = GetPosition();

	if (velocity.x > 0.0f || velocity.x < 0.0f)
		moving = true;
	else
		moving = false;

	if (inputManager->KeyDown(SDL_SCANCODE_D)) {

		PlayAnim(RUNNING);
		velocity.x = 200.0f * timer->DeltaTime();
	}
	else if (inputManager->KeyDown(SDL_SCANCODE_A)) {
		
		PlayAnim(RUNNING);
		velocity.x = -200.0f * timer->DeltaTime();
	}
	else {

		PlayAnim(IDLE);
		velocity.x = 0.0f;
	}
		
	Translate(velocity.x * VEC2_RIGHT);
		
	if (inputManager->KeyPressed(SDL_SCANCODE_SPACE))
		Jump();

	if (!grounded) {

		velocity.y += g * timer->DeltaTime();

		//position.y += velocity.y * timer->DeltaTime() + 0.5f * g * timer->DeltaTime() * timer->DeltaTime();

		deltaY = velocity.y * timer->DeltaTime() + 0.5f * g * timer->DeltaTime() * timer->DeltaTime();
	}

	Translate(deltaY * VEC2_UP);

	if (currentAnim == IDLE)
		idleAnim->Update();
	else if (currentAnim == RUNNING)
		runAnim->Update();
}

void Player::LateUpdate() {

	Sprite* col = collision->AABB(GetRect());

	if (col != nullptr) {

		if (GetRect().y < col->GetRect().y || GetRect().y > col->GetRect().y) {

			Position(Vector2(GetPosition().x, prevPos.y));
			if (currentAnim == IDLE)
				idleAnim->Update();
			else if (currentAnim == RUNNING)
				runAnim->Update();

			velocity.y = 0.0f;
		}
	}
}

void Player::Render() {

	if (currentAnim == IDLE)
		idleAnim->Render();
	else if (currentAnim == RUNNING)
		runAnim->Render();
}

SDL_Rect Player::GetRect() {
	if (currentAnim == IDLE)
		return idleAnim->GetRect();
	return runAnim->GetRect();
}