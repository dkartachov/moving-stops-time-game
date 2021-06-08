#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"
#include "Collision.h"

class Player : public GameEntity {
public:
	enum ANIM {IDLE = 0, RUNNING};
public:
	Player(Collision* coll);
	~Player();

	void Grounded(bool state);
	bool IsMoving();
	void Jump();

	ANIM CurrentAnim();
	void PlayAnim(ANIM anim);

	void Update();
	void LateUpdate();
	void Render();

	SDL_Rect GetRect();

private:
	Collision* collision;
	InputManager* inputManager;
	Timer* timer;

	ANIM currentAnim;
	AnimatedSprite* idleAnim;
	AnimatedSprite* runAnim;

	Vector2 prevPos;
	Vector2 position;
	Vector2 velocity;

	bool moving;
	bool grounded;
	float deltaY;
	const float g = 300;
};