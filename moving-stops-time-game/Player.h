#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"
#include "Collision.h"

class Player : public GameEntity {
public:
	Player(Collision* coll);
	~Player();

	void Grounded(bool state);
	bool IsMoving();
	void Jump();

	void Update();
	void LateUpdate();
	void Render();

	SDL_Rect GetRect();

private:
	Collision* collision;
	InputManager* inputManager;
	Timer* timer;

	Sprite* staticSprite;
	AnimatedSprite* idleAnim;

	Vector2 prevPos;
	Vector2 position;
	Vector2 velocity;

	bool moving;
	bool grounded;
	float deltaY;
	const float g = 300;
};