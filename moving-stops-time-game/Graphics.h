#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

class Graphics {
public:
	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	Graphics();
	bool Init();

	SDL_Texture* LoadTexture(std::string path);
	SDL_Texture* CreateText(TTF_Font* font, std::string text, SDL_Color color);

	void DrawTexture(SDL_Texture* texture, SDL_Rect* clip = NULL, SDL_Rect* rect = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Clear();
	void Render();
	void Exit();
public:
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 800;
private:
	const char* TITLE = "Moving stops time";
	static Graphics* instance;
	static bool initialized;
	SDL_Window* window;
	SDL_Renderer* renderer;
};