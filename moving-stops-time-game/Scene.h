#pragma once
#include "Player.h"
#include "Collision.h"
#include "Camera.h"

class Scene {

public:
	Scene();
	~Scene();

	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

private:
	int levelWidth, levelHeight;

	Collision* collision;
	Camera* camera;
	Player* player;

};