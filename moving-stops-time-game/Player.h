#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"
#include "Collision.h"
#include "PhysicsObject.h"

class Player : public GameEntity {
public:
	enum ANIM {IDLE = 0, RUNNING, JUMP, LAND};
public:
	Player(Collision* coll);
	~Player();

	BoxCollider* GetBox();

	void Grounded(bool state);
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
	BoxCollider* box;
	Collision* collision;
	InputManager* inputManager;
	Timer* timer;

	ANIM currentAnim;
	AnimatedSprite* idleAnim;
	AnimatedSprite* runAnim;
	AnimatedSprite* jumpAnim;
	AnimatedSprite* landAnim;

	Vector2 prevPos;
	Vector2 position;
	Vector2 velocity;

	bool moving;
	bool flipped;
	bool grounded;
	float deltaY;
	const float g = 300;
};