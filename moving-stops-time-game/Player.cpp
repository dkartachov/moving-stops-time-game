#include "Player.h"

Player::Player() : PhysicsObject(40, 100) {

	Dynamic(true);

	sliding = false;
	jumping = false;
	jumpTime = 0.25f;
	jumpTimer = 0.0f;

	touchingWall = false;
	grounded = false;

	groundedBox = new BoxCollider(18, 4);
	groundedBox->Parent(this);
	groundedBox->Position(VEC2_ZERO);
	groundedBox->Position(Vector2(0.0f, 50));

	wallBox = new BoxCollider(4, 20);
	wallBox->Parent(this);
	wallBox->Position(VEC2_ZERO);
	wallBox->Position(Vector2(-20, 0));

	flipped = false;
	moving = false;

	inputManager = InputManager::Instance();
	timer = Timer::Instance();

	Velocity(VEC2_ZERO);

	idleAnim = new AnimatedSprite("idle-cycle.png", 0, 0, 122, 122, 8, 0.8);
	idleAnim->Parent(this);
	idleAnim->Position(VEC2_ZERO);

	runAnim = new AnimatedSprite("run-cycle.png", 0, 0, 122, 122, 6, 0.8);
	runAnim->Parent(this);
	runAnim->Position(VEC2_ZERO);

	jumpAnim = new AnimatedSprite("jump-cycle.png", 0, 0, 122, 122, 3, 0.3);
	jumpAnim->WrapMode(AnimatedSprite::once);
	jumpAnim->Parent(this);
	jumpAnim->Position(VEC2_ZERO);

	landAnim = new AnimatedSprite("jump-cycle.png", 122 * 3, 0, 122, 122, 2, 1);
	landAnim->WrapMode(AnimatedSprite::once);
	landAnim->Parent(this);
	landAnim->Position(VEC2_ZERO);
}

Player::~Player() {

	inputManager = nullptr;
}

bool Player::IsMoving() {
	return moving;
}

void Player::Jump() {

	Velocity(Vector2(GetVelocity().x, -jumpSpeed));
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

	grounded = Collision::Instance()->AllAABB(*groundedBox, { "Ground" , "Platform" });
	touchingWall = Collision::Instance()->AllAABB(*wallBox, { "Wall" });

	bool onPlatform = false;
	std::string s;
	if (Collision::Instance()->GetCurrentCollider() != nullptr)
		s = Collision::Instance()->GetCurrentCollider()->GetTag();

	if (grounded && s == "Platform") {
		onPlatform = true;
	}
		
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
		Velocity(Vector2(moveSpeed, GetVelocity().y));
	else if (inputManager->KeyDown(SDL_SCANCODE_A))
		Velocity(Vector2(-moveSpeed, GetVelocity().y));

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
			
	if (grounded) {

		if (inputManager->KeyPressed(SDL_SCANCODE_SPACE)) {

			Jump();
			jumping = true;
		}
	}
	
	if (inputManager->KeyDown(SDL_SCANCODE_SPACE) && jumping) {

		jumpTimer += timer->DeltaTime();

		if (jumpTimer >= jumpTime) {

			jumping = false;
			jumpTimer = 0.0f;
			GravityModifier(1);
		}
		else
			GravityModifier(0.5f);
	}

	if (inputManager->KeyReleased(SDL_SCANCODE_SPACE)) {

		jumping = false;
		jumpTimer = 0.0f;
		GravityModifier(1);
	}

	if (!grounded && !sliding) {

		if (GetVelocity().y < 0.0f) {
			
			PlayAnim(JUMP);
			//GravityModifier(1);
		}
		if (GetVelocity().y > 0.0f) {
			
			PlayAnim(LAND);
			GravityModifier(2.5f);
		}
	}

	if (grounded)
		landAnim->Reset();

	if (touchingWall) {

		if (inputManager->KeyDown(SDL_SCANCODE_A) && !sliding) {

			sliding = true;
			Velocity(Vector2(GetVelocity().x, 0.0f));
		}
	}
	else if (!touchingWall) {

		sliding = false;
	}

	if (sliding) {

		GravityModifier(0.2f);
	}

	//if (touchingWall && inputManager->KeyDown(SDL_SCANCODE_A) && !sliding) {

	//	sliding = true;
	//	Velocity(Vector2(GetVelocity().x, 0.0f));
	//	//GravityModifier(1);
	//}
	//
	//if (touchingWall && inputManager->KeyReleased(SDL_SCANCODE_A)) {

	//	sliding = false;
	//	//GravityModifier(2.5f);
	//}

	//if (sliding) {

	//	GravityModifier(0.5f);
	//}

	//printf("X Position: %f , X Velocity: %f\n", GetPosition().x, GetVelocity().x);
	//printf("Y Position: %f , Y Velocity: %f\n", GetPosition().y, GetVelocity().y);

	PhysicsObject::Update();
	groundedBox->Update();
	wallBox->Update();

	if ((inputManager->KeyDown(SDL_SCANCODE_D)|| inputManager->KeyDown(SDL_SCANCODE_A) || !grounded) && !onPlatform)
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