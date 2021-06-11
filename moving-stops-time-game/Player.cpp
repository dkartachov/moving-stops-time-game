#include "Player.h"

Player::Player(Collision* coll) : PhysicsObject(20, 50) {

	Active(false);
	Dynamic(true);

	Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	collision = coll;

	flipped = false;
	moving = false;
	grounded = false;

	inputManager = InputManager::Instance();
	timer = Timer::Instance();

	velocity = VEC2_ZERO;

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

void Player::Grounded(bool state) {
	grounded = state;
}

bool Player::IsMoving() {
	return moving;
}

void Player::Jump() {

	grounded = false;
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

	if (GetVelocity().Magnitude() > 0.1f)
		moving = true;
	else
		moving = false;

	if (GetVelocity().x > 0.0f) {

		runAnim->FlipY(SDL_FLIP_NONE);
		idleAnim->FlipY(SDL_FLIP_NONE);
		jumpAnim->FlipY(SDL_FLIP_NONE);
		landAnim->FlipY(SDL_FLIP_NONE);
	}
	else if (GetVelocity().x < 0.0f) {

		runAnim->FlipY(SDL_FLIP_HORIZONTAL);
		idleAnim->FlipY(SDL_FLIP_HORIZONTAL);
		jumpAnim->FlipY(SDL_FLIP_HORIZONTAL);
		landAnim->FlipY(SDL_FLIP_HORIZONTAL);
	}

	if (inputManager->KeyDown(SDL_SCANCODE_D))
		Velocity(Vector2(200.0f, GetVelocity().y));
	else if (inputManager->KeyDown(SDL_SCANCODE_A))
		Velocity(Vector2(-200.0f, GetVelocity().y));
	else
		Velocity(Vector2(0.0f, GetVelocity().y));

	if (grounded) {

		if (abs(GetVelocity().x) > 0.0f) {

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

	printf("Velocity: (%f, %f)\n", GetVelocity().x, GetVelocity().y);

	if (!grounded) {

		if (GetVelocity().y < 0.0f)
			PlayAnim(JUMP);
		if (GetVelocity().y > 0.0f)
			PlayAnim(LAND);
	}

	if (grounded)
		landAnim->Reset();

	PhysicsObject::Update();
}

bool Player::xCausesCollision(PhysicsObject* obj) {

	bool hasCollision = collision->AABB(this->GetBox()->GetBox(), obj->GetBox()->GetBox());
	Position(Vector2(GetPosition().x - GetVelocity().x * timer->DeltaTime(), GetPosition().y));
	bool hadCollision = collision->AABB(this->GetBox()->GetBox(), obj->GetBox()->GetBox());
	Position(Vector2(GetPosition().x + GetVelocity().x * timer->DeltaTime(), GetPosition().y));

	return hasCollision && !hadCollision;
}

bool Player::yCausesCollision(PhysicsObject* obj) {

	bool hasCollision = collision->AABB(this->GetBox()->GetBox(), obj->GetBox()->GetBox());
	Position(Vector2(GetPosition().x, GetPosition().y - GetVelocity().y * timer->DeltaTime()));
	bool hadCollision = collision->AABB(this->GetBox()->GetBox(), obj->GetBox()->GetBox());
	Position(Vector2(GetPosition().x, GetPosition().y + GetVelocity().y * timer->DeltaTime()));

	return hasCollision && !hadCollision;
}

void Player::LateUpdate() {

	for (auto x : collision->GetColliders()) {

		while (xCausesCollision(x)) {

			Position(Vector2(GetPosition().x - GetVelocity().x * timer->DeltaTime(), GetPosition().y));
		}

		while (yCausesCollision(x)) {

			Position(Vector2(GetPosition().x, GetPosition().y - GetVelocity().y * timer->DeltaTime()));
			grounded = true;
			Velocity(Vector2(GetVelocity().x, 0.0f));
		}
	}
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