#pragma once
#include "Collision.h"
#include "Camera.h"

class Scene {

public:
	Scene(int levelWidth, int levelHeight);
	~Scene();

	virtual void Update();
	virtual void LateUpdate();
	virtual void Render();

protected:
	int levelWidth, levelHeight;
	Collision* collision;
	Camera* camera;	
};