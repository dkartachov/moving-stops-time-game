#pragma once
#include "Player.h"
#include "Collision.h"
#include "PhysicsObject.h"

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
	PhysicsObject* ground1, * ground2, * wall, * platform;
	int platformDirection = 1;
};