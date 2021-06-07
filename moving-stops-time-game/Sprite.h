#pragma once
#include "GameEntity.h"
#include "AssetManager.h"

class Sprite : public GameEntity {
public:
	Sprite(const char* filename);
	Sprite(const char* filename, int x, int y, int w, int h);
	Sprite(std::string text, std::string fontPath, int size, SDL_Color color = {0, 0, 0});

	SDL_Rect GetRect();
	virtual void Update();
	virtual void Render();
protected:
	SDL_Texture* texture;
	Graphics* graphics;
	int width, height;
	bool clipped;
	SDL_Rect renderRect;
	SDL_Rect clipRect;
};