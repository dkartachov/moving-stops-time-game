#include "AssetManager.h"

AssetManager* AssetManager::instance = NULL;

AssetManager* AssetManager::Instance() {

	if (instance == NULL)
		instance = new AssetManager();
	return instance;
}

void AssetManager::Release() {

	delete instance;
	instance = NULL;
}

AssetManager::AssetManager() {

}

AssetManager::~AssetManager() {

	for (auto texture : textures)
		if (texture.second != NULL)
			SDL_DestroyTexture(texture.second);

	textures.clear();

	for (auto text : texts)
		if (text.second != NULL)
			SDL_DestroyTexture(text.second);

	texts.clear();

	for (auto font : fonts)
		if (font.second != NULL)
			TTF_CloseFont(font.second);

	fonts.clear();

	for (auto track : music)
		if (track.second != NULL)
			Mix_FreeMusic(track.second);

	music.clear();

	for (auto sfx : sfxs)
		if (sfx.second != NULL)
			Mix_FreeChunk(sfx.second);

	sfxs.clear();
}

SDL_Texture* AssetManager::GetTexture(std::string filename) {

	std::string path = "Assets/Sprites/";
	path.append(filename);

	if (textures[path] == nullptr)
		textures[path] = Graphics::Instance()->LoadTexture(path.c_str());

	return textures[path];
}

SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color) {

	TTF_Font* font = GetFont(filename, size);

	std::string key = text + filename + (char)size + (char)color.r + (char)color.g + (char)color.b;

	if (texts[key] == nullptr)
		texts[key] = Graphics::Instance()->CreateText(font, text, color);

	return texts[key];
}

TTF_Font* AssetManager::GetFont(std::string filename, int size) {

	std::string path = "Assets/Fonts/";
	path.append(filename);
	std::string key = path + (char)size;

	if (fonts[key] == nullptr) {

		fonts[key] = TTF_OpenFont(path.c_str(), size);

		if (fonts[key] == nullptr)
			printf("Font loading error\n Font: %s\n Error: %s\n", filename.c_str(), TTF_GetError());
	}

	return fonts[key];
}

Mix_Music* AssetManager::GetMusic(std::string filename) {

	std::string path = "Assets/Music/";
	path.append(filename);

	if (music[path] == nullptr) {

		music[path] = Mix_LoadMUS(path.c_str());

		if (music[path] == NULL)
			printf("Music load error\n File: %s\n Error: %s\n", filename.c_str(), Mix_GetError());
	}

	return music[path];
}

Mix_Chunk* AssetManager::GetSFX(std::string filename) {

	std::string path = "Assets/SFX/";
	path.append(filename);

	if (sfxs[path] == nullptr) {

		sfxs[path] = Mix_LoadWAV(path.c_str());

		if (sfxs[path] == NULL)
			printf("SFX load error\n File: %s\n Error: %s\n", filename.c_str(), Mix_GetError());
	}

	return sfxs[path];
}