#pragma once
#include "AnimatedSprite.h"
#include "InputManager.h"

class LevelOne : public GameEntity {
public:
	LevelOne();
	~LevelOne();

	void Update(GameEntity* pauseMenu, GameEntity* player);
	void Render(GameEntity* player);
private:
	InputManager* inputManager;
	Sprite* sprite;
};