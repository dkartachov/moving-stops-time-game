#include "Graphics.h"

Graphics* Graphics::instance = NULL;
bool Graphics::initialized = false;

Graphics* Graphics::Instance() {
	if (instance == NULL)
		instance = new Graphics();

	return instance;
}

void Graphics::Release() {
	delete instance;
	instance = NULL;

	initialized = false;
}

bool Graphics::Initialized() {
	return initialized;
}

Graphics::Graphics() {

	initialized = Init();
}

Graphics::~Graphics() {

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init() {
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("Cannot create window: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Cannot create renderer: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) {
		printf("Image initialization error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1) {
		printf("TTF initilization error: %s\n", TTF_GetError());
		return false;
	}

	return true;
}

SDL_Texture* Graphics::LoadTexture(std::string path) {

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL)
		printf("Image load error: %s\n", IMG_GetError());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		printf("Create texture error: %s\n", SDL_GetError());

	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture* Graphics::CreateText(TTF_Font* font, std::string text, SDL_Color color) {

	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL)
		printf("Text create error: %s", TTF_GetError());

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
		printf("Text render error: %s", SDL_GetError());

	SDL_FreeSurface(surface);

	return texture;
}

void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* clip, SDL_Rect* rect, float angle, SDL_RendererFlip flip) {

	SDL_RenderCopyEx(renderer, texture, clip, rect, angle, NULL, flip);
}

void Graphics::Clear() {
	SDL_RenderClear(renderer);
}

void Graphics::Render() {
	SDL_RenderPresent(renderer);
}

void Graphics::Exit() {

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}