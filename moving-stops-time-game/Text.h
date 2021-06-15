#pragma once
#include "GameEntity.h"
#include "AssetManager.h"

class Text : public GameEntity {

public:
	Text(std::string text, std::string fontPath, int size, SDL_Color color = { 0, 0, 0 });

	void Render();
	
private:
	SDL_Texture* texture;
	Graphics* graphics;
	int width, height;
	SDL_Rect renderRect;
	SDL_Rect clipRect;
};