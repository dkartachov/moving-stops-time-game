#include "Player.h"

Player::Player(Collision* coll) : PhysicsObject(20, 50) {

	Active(false);

	Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	collision = coll;

	flipped = false;
	moving = false;
	grounded = false;

	//box = new BoxCollider(20, 50);
	//box->Parent(this);
	//box->Position(VEC2_ZERO);

	inputManager = InputManager::Instance();
	timer = Timer::Instance();

	velocity = VEC2_ZERO;

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
	velocity.y = -200.0f;
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

	if (velocity.Magnitude() > 0.1f)
		moving = true;
	else
		moving = false;

	if (velocity.x > 0.0f) {

		runAnim->FlipY(SDL_FLIP_NONE);
		idleAnim->FlipY(SDL_FLIP_NONE);
		jumpAnim->FlipY(SDL_FLIP_NONE);
		landAnim->FlipY(SDL_FLIP_NONE);
	}
	else if (velocity.x < 0.0f) {

		runAnim->FlipY(SDL_FLIP_HORIZONTAL);
		idleAnim->FlipY(SDL_FLIP_HORIZONTAL);
		jumpAnim->FlipY(SDL_FLIP_HORIZONTAL);
		landAnim->FlipY(SDL_FLIP_HORIZONTAL);
	}

	if (inputManager->KeyDown(SDL_SCANCODE_D))
		velocity.x = 200.0f * timer->DeltaTime();
	else if (inputManager->KeyDown(SDL_SCANCODE_A))
		velocity.x = -200.0f * timer->DeltaTime();
	else
		velocity.x = 0.0f;

	if (grounded) {

		if (abs(velocity.x) > 0.0f) {

			PlayAnim(RUNNING);
			idleAnim->Reset();
		}
		else {

			PlayAnim(IDLE);
			runAnim->Reset();
		}
	}
		
	Translate(velocity.x * VEC2_RIGHT);
		
	if (inputManager->KeyPressed(SDL_SCANCODE_SPACE))
		Jump();


	velocity.y += g * timer->DeltaTime();
	deltaY = velocity.y * timer->DeltaTime() + 0.5f * g * timer->DeltaTime() * timer->DeltaTime();

	Translate(deltaY * VEC2_UP);
	

	if (!grounded) {

		if (velocity.y < 0.0f)
			PlayAnim(JUMP);
		if (velocity.y > 0.0f)
			PlayAnim(LAND);
	}

	if (grounded)
		landAnim->Reset();

	PhysicsObject::Update();
		
	//box->Update();
}

bool Player::xCausesCollision(PhysicsObject* obj) {

	bool hasCollision = collision->AABB(this->GetBox()->GetBox(), obj->GetBox()->GetBox());
	Position(Vector2(GetPosition().x - velocity.x, GetPosition().y));
	PhysicsObject::Update();
	//box->Update();
	bool hadCollision = collision->AABB(this->GetBox()->GetBox(), obj->GetBox()->GetBox());
	Position(Vector2(GetPosition().x + velocity.x, GetPosition().y));
	PhysicsObject::Update();
	//box->Update();

	return hasCollision && !hadCollision;
}

bool Player::yCausesCollision(PhysicsObject* obj) {

	bool hasCollision = collision->AABB(this->GetBox()->GetBox(), obj->GetBox()->GetBox());
	Position(Vector2(GetPosition().x, GetPosition().y - deltaY));
	PhysicsObject::Update();
	//box->Update();
	bool hadCollision = collision->AABB(this->GetBox()->GetBox(), obj->GetBox()->GetBox());
	Position(Vector2(GetPosition().x, GetPosition().y + deltaY));
	PhysicsObject::Update();
	//box->Update();

	return hasCollision && !hadCollision;
}

void Player::LateUpdate() {

	for (auto x : collision->GetColliders()) {

		while (xCausesCollision(x)) {

			Position(Vector2(GetPosition().x - velocity.x, GetPosition().y));
			PhysicsObject::Update();
			//box->Update();
		}

		while (yCausesCollision(x)) {

			Position(Vector2(GetPosition().x, GetPosition().y - deltaY));
			grounded = true;
			velocity.y = 0.0f;
			PhysicsObject::Update();
			//box->Update();
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