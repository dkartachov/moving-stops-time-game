#pragma once
#include "GameEntity.h"
#include "Graphics.h"

class Camera : public GameEntity {

public:
	static Camera* Instance();
	static void Release();

	void Size(int width);

private:
	Camera();

	static Camera* instance;
	int w, h;
};