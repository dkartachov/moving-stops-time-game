#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"

class Player : public GameEntity {
public:
	Player();
	~Player();

	void Update();
	void Render();
private:
	InputManager* inputManager;
	Timer* timer;

	GameEntity* player;
	Sprite* staticSprite;
	AnimatedSprite* idleAnim;

	Vector2 position;
	Vector2 velocity;
};