#include "AudioManager.h"

AudioManager* AudioManager::instance = NULL;

AudioManager* AudioManager::Instance() {

	if (instance == NULL)
		instance = new AudioManager();

	return instance;
}

void AudioManager::Release() {
	
	delete instance;
	instance = NULL;
}

AudioManager::AudioManager() {
	
	assetManager = AssetManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		printf("Mixer initialization error: %s", Mix_GetError());
}

AudioManager::~AudioManager() {

	assetManager = NULL;
	Mix_Quit();
}

void AudioManager::PlayMusic(std::string filename, int loops) {
	Mix_PlayMusic(assetManager->GetMusic(filename), loops);
}

void AudioManager::PauseMusic() {
	
	if (Mix_PlayingMusic() != 0)
		Mix_PauseMusic();
}

void AudioManager::ResumeMusic() {
	
	if (Mix_PausedMusic() != 0)
		Mix_ResumeMusic();
}

void AudioManager::PlaySFX(std::string filename, int loops, int channel) {
	Mix_PlayChannel(channel, assetManager->GetSFX(filename), loops);
}