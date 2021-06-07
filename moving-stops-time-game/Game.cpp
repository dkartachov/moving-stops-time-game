#include "Game.h"

Game* Game::instance = NULL;

Game* Game::Instance() {
	if (instance == NULL)
		instance = new Game();

	return instance;
}

void Game::Release() {
	delete instance;
	instance = NULL;
}

Game::Game() {

	quit = false;

	timer = Timer::Instance();
	graphics = Graphics::Instance();
	assetManager = AssetManager::Instance();
	inputManager = InputManager::Instance();
	audioManager = AudioManager::Instance();

	sceneOne = new SceneOne();
}

void Game::EarlyUpdate() {
	timer->Reset();
	inputManager->Update();
}

void Game::Update() {

	////GAME ENTITY UPDATES HERE////
	
	sceneOne->Update();

	///////////////////////////////
}

void Game::LateUpdate() {

	////COLLISION DETECTION HERE////

	sceneOne->LateUpdate();

	///////////////////////////////

	inputManager->UpdatePreviousInput();
}

void Game::Render() {

	graphics->Clear();

	////RENDER ENTITIES HERE////

	sceneOne->Render();
		
	///////////////////////////

	graphics->Render();
}

void Game::Run() {

	while (!quit) {

		timer->Update();

		while (SDL_PollEvent(&events))
			if (events.type == SDL_QUIT)
				quit = true;

		if (timer->DeltaTime() >= 1.0f / FRAME_RATE) {

			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}

void Game::Quit() {
	graphics->Exit();
}