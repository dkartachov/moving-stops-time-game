#pragma once
#include "GameEntity.h"
#include "AssetManager.h"
#include "BoxCollider.h"

class Sprite : public GameEntity {
public:
	Sprite(const char* filename);
	Sprite(const char* filename, int x, int y, int w, int h);
	Sprite(std::string text, std::string fontPath, int size, SDL_Color color = {0, 0, 0});

	BoxCollider* GetBox();
	void FlipY(SDL_RendererFlip flipY);
	virtual void Render();
protected:
	SDL_RendererFlip flipY;
	SDL_Texture* texture;
	Graphics* graphics;
	int width, height;
	bool clipped;
	BoxCollider* box;
	SDL_Rect renderRect;
	SDL_Rect clipRect;
};