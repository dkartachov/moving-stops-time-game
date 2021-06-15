#pragma once
#include "Player.h"
#include "Collision.h"
#include "PhysicsObject.h"
#include "Camera.h"

class SceneOne {
public:
	SceneOne();
	~SceneOne();

	void Update();
	void LateUpdate();
	void Render();

private:
	int levelWidth, levelHeight;
	Collision* collision;
	Player* player;
	Camera* camera;
	PhysicsObject* ground1, * platform, * platform2;
	int platformDirection = 1;
	int platform2Direction = 1;
};