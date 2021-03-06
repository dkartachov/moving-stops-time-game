#pragma once
#include "Player.h"
#include "PhysicsObject.h"
#include "Scene.h"

class SceneOne : public Scene {
public:
	SceneOne();
	~SceneOne();

	void Update();
	void Render();

private:
	Player* player;
	PhysicsObject* ground1;
	PhysicsObject* ground2;
	PhysicsObject* platform1;
	PhysicsObject* wall;
	int platformDirection = 1;
	int platform2Direction = 1;
};