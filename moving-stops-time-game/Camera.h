#pragma once
#include "GameEntity.h"
#include "Graphics.h"

class Camera : public GameEntity {

public:
	static Camera* Instance();
	static void Release();

	int GetWidth();
	int GetHeight();
private:
	Camera();

	static Camera* instance;
	int w, h;
};