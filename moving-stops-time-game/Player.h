#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"
#include "Collision.h"
#include "PhysicsObject.h"

class Player : public PhysicsObject {
public:
	enum ANIM {IDLE = 0, RUNNING, JUMP, LAND};
public:
	Player();
	~Player();

	bool IsMoving();
	void Jump();

	ANIM CurrentAnim();
	void PlayAnim(ANIM anim);

	void Update();
	void LateUpdate();
	void Render();

private:
	InputManager* inputManager;
	Timer* timer;

	ANIM currentAnim;
	AnimatedSprite* idleAnim;
	AnimatedSprite* runAnim;
	AnimatedSprite* jumpAnim;
	AnimatedSprite* landAnim;

	BoxCollider* wallBox;
	BoxCollider* groundedBox;

	const int moveSpeed = 250;
	const int jumpSpeed = 300;

	float jumpTime, jumpTimer;
	bool jumping;
	bool wallJumping;

	bool touchingWall;
	bool sliding;
	
	bool grounded;
	bool moving;

	bool flipped;
};