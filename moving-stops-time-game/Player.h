#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"

class Player : public GameEntity {
public:
	Player();
	~Player();

	void Jump();

	void Update();
	void LateUpdate();
	void Render();

	SDL_Rect GetRect();

private:
	InputManager* inputManager;
	Timer* timer;

	Sprite* staticSprite;
	AnimatedSprite* idleAnim;

	Vector2 position;
	Vector2 velocity;

	bool grounded;
	float deltaY;
	const float g = 200;
};