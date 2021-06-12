#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"
#include "Collision.h"
#include "PhysicsObject.h"

class Player : public PhysicsObject {
public:
	enum ANIM {IDLE = 0, RUNNING, JUMP, LAND};
public:
	Player(Collision* coll);
	~Player();

	bool IsMoving();
	void Jump();

	ANIM CurrentAnim();
	void PlayAnim(ANIM anim);

	bool xCausesCollision(PhysicsObject* b);
	bool yCausesCollision(PhysicsObject* b);

	void Update();
	void LateUpdate();
	void Render();

private:
	Collision* collision;
	InputManager* inputManager;
	Timer* timer;

	ANIM currentAnim;
	AnimatedSprite* idleAnim;
	AnimatedSprite* runAnim;
	AnimatedSprite* jumpAnim;
	AnimatedSprite* landAnim;

	Vector2 position;
	Vector2 velocity;

	bool grounded;
	bool moving;
	bool flipped;
	float deltaY;
	const float g = 300;
};