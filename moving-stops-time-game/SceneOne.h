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

	Player* player;
	Sprite* ground, *ground1;
	Sprite* platform;
	int platformDirection = 1;
};