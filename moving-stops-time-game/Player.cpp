#include "Player.h"

Player::Player() : PhysicsObject(20, 50) {

	Active(false);
	Dynamic(true);

	Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	grounded = false;
	groundedBox = new BoxCollider(18, 4);
	groundedBox->Parent(this);
	groundedBox->Position(VEC2_ZERO);
	groundedBox->Position(Vector2(0.0f, 25));

	flipped = false;
	moving = false;

	inputManager = InputManager::Instance();
	timer = Timer::Instance();

	Velocity(VEC2_ZERO);

	idleAnim = new AnimatedSprite("idle.png", 0, 0, 80, 80, 18, 1);
	idleAnim->Parent(this);
	idleAnim->Position(VEC2_ZERO);

	runAnim = new AnimatedSprite("run.png", 0, 0, 80, 80, 24, 1);
	runAnim->Parent(this);
	runAnim->Position(VEC2_ZERO);

	jumpAnim = new AnimatedSprite("jump.png", 0, 0, 80, 80, 8, 0.5);
	jumpAnim->WrapMode(AnimatedSprite::once);
	jumpAnim->Parent(this);
	jumpAnim->Position(VEC2_ZERO);

	landAnim = new AnimatedSprite("jump.png", 80 * 8, 0, 80, 80, 7, 0.85);
	landAnim->WrapMode(AnimatedSprite::once);
	landAnim->Parent(this);
	landAnim->Position(VEC2_ZERO);

	Scale(2 * VEC2_ONE);
}

Player::~Player() {

	inputManager = nullptr;
}

bool Player::IsMoving() {
	return moving;
}

void Player::Jump() {

	Velocity(Vector2(GetVelocity().x, -200.0f));
	jumpAnim->Reset();
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

	case JUMP:

		jumpAnim->Play();
		break;

	case LAND:

		landAnim->Play();
		break;

	default:

		break;
	}
}

void Player::Update() {

	Vector2 prev = GetPosition();

	grounded = Collision::Instance()->AllAABB(*groundedBox, "Ground");
	//printf("Grounded = %d\n", grounded);

	if (inputManager->KeyDown(SDL_SCANCODE_D)) {

		runAnim->FlipY(SDL_FLIP_NONE);
		idleAnim->FlipY(SDL_FLIP_NONE);
		jumpAnim->FlipY(SDL_FLIP_NONE);
		landAnim->FlipY(SDL_FLIP_NONE);
	}
	else if (inputManager->KeyDown(SDL_SCANCODE_A)) {

		runAnim->FlipY(SDL_FLIP_HORIZONTAL);
		idleAnim->FlipY(SDL_FLIP_HORIZONTAL);
		jumpAnim->FlipY(SDL_FLIP_HORIZONTAL);
		landAnim->FlipY(SDL_FLIP_HORIZONTAL);
	}

	if (inputManager->KeyDown(SDL_SCANCODE_D))
		Velocity(Vector2(200.0f, GetVelocity().y));
	else if (inputManager->KeyDown(SDL_SCANCODE_A))
		Velocity(Vector2(-200.0f, GetVelocity().y));

	if (inputManager->KeyReleased(SDL_SCANCODE_D) || inputManager->KeyReleased(SDL_SCANCODE_A))
		Velocity(Vector2(0.0f, GetVelocity().y));

	if (grounded) {

		if (inputManager->KeyDown(SDL_SCANCODE_D) || inputManager->KeyDown(SDL_SCANCODE_A)) {

			PlayAnim(RUNNING);
			idleAnim->Reset();
		}
		else {

			PlayAnim(IDLE);
			runAnim->Reset();
		}
	}
				
	if (inputManager->KeyPressed(SDL_SCANCODE_SPACE))
		Jump();

	if (!grounded) {

		if (GetVelocity().y < 0.0f)
			PlayAnim(JUMP);
		if (GetVelocity().y > 0.0f)
			PlayAnim(LAND);
	}

	if (grounded)
		landAnim->Reset();

	//printf("X Position: %f , X Velocity: %f\n", GetPosition().x, GetVelocity().x);
	//printf("Y Position: %f , Y Velocity: %f\n", GetPosition().y, GetVelocity().y);

	PhysicsObject::Update();
	groundedBox->Update();

	Vector2 pos = GetPosition();
	float delx = pos.x - prev.x;
	float dely = pos.y - prev.y;

	if (abs(delx) > 1 || !grounded)
		moving = true;
	else
		moving = false;
}

void Player::LateUpdate() {

}

void Player::Render() {

	if (currentAnim == IDLE)
		idleAnim->Render();
	if (currentAnim == RUNNING)
		runAnim->Render();
	if (currentAnim == JUMP)
		jumpAnim->Render();
	if (currentAnim == LAND)
		landAnim->Render();
}