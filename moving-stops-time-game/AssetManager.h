#pragma once
#include "Graphics.h"
#include <SDL_mixer.h>
#include <map>

class AssetManager {
public:
	AssetManager();
	~AssetManager();

	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(std::string filename);

	SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color);
	TTF_Font* GetFont(std::string filename, int size);

	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);

private:
	static AssetManager* instance;
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, SDL_Texture*> texts;
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> sfxs;
};