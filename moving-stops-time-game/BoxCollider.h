#pragma once
#include "GameEntity.h"
#include <SDL.h>

class BoxCollider : public GameEntity {
public:
	BoxCollider(int w, int h);

	SDL_Rect GetBox();
	void Update();
private:
	int width, height;
	SDL_Rect box;
};