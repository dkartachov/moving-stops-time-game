#pragma once
#include "Player.h"
#include "Collision.h"

class SceneOne {
public:
	SceneOne();
	~SceneOne();

	void Update();
	void LateUpdate();
	void Render();

private:
	Collision* collision;
	Player* player;
	Sprite* ground, *ground1;
	Sprite* wall;
	Sprite* platform;
	int platformDirection = 1;
};