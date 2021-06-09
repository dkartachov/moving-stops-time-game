#include "Player.h"

Player::Player(Collision* coll) {

	Active(false);

	Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));

	collision = coll;

	flipped = false;
	moving = false;
	grounded = false;

	box = new BoxCollider(20, 50);
	box->Parent(this);
	box->Position(VEC2_ZERO);

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

	prevPos = GetPosition();

	printf("%f\n", velocity.Magnitude());

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
		
	box->Update();

	//printf("Player pos: (%f, %f)\n", GetPosition().x, GetPosition().y);
}

void Player::LateUpdate() {

	collision->GetColliders(box->GetBox());

	Sprite* col = collision->AABB(box->GetBox());

	if (col != nullptr) {

		if (box->GetBox().y < col->GetRect().y + col->GetRect().h || box->GetBox().y + box->GetBox().h > col->GetRect().y) {

			if (box->GetBox().y + box->GetBox().h > col->GetRect().y)
				grounded = true;

			Position(Vector2(GetPosition().x, prevPos.y));
			box->Update();
			velocity.y = 0.0f;
		}

		if (box->GetBox().x + box->GetBox().w > col->GetRect().x || box->GetBox().x < col->GetRect().x + col->GetRect().w) {

			Position(Vector2(prevPos.x, GetPosition().y));
			box->Update();
			velocity.x = 0.0f;
		}
	}

	col = nullptr;
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