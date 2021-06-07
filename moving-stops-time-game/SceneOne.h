#pragma once
#include "Player.h"

class SceneOne {
public:
	SceneOne();
	~SceneOne();

	void Update();
	void Render();

private:

	Player* player;
	Sprite* ground;
};