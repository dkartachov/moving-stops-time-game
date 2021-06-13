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
	collision = Collision::Instance();

	sceneOne = new SceneOne();
}

Game::~Game() {

	Timer::Release();
	timer = nullptr;

	Graphics::Release();
	graphics = nullptr;

	AssetManager::Release();
	assetManager = nullptr;

	InputManager::Release();
	inputManager = nullptr;

	AudioManager::Release();
	audioManager = nullptr;

	Collision::Release();
	collision = nullptr;

	delete sceneOne;
	sceneOne = nullptr;
}

void Game::EarlyUpdate() {

	timer->Reset();
	inputManager->Update();
}

void Game::Update() {

	////GAME ENTITY UPDATES HERE////

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_DELETE)) {
		delete sceneOne;
		sceneOne = nullptr;
	}
	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_RETURN)) {
		delete sceneOne;
		sceneOne = nullptr;
		sceneOne = new SceneOne();
	}
	
	if (sceneOne != nullptr)
		sceneOne->Update();

	///////////////////////////////
}

void Game::LateUpdate() {

	////COLLISION DETECTION HERE////

	if (sceneOne != nullptr)
		sceneOne->LateUpdate();

	///////////////////////////////

	inputManager->UpdatePreviousInput();
}

void Game::Render() {

	graphics->Clear();

	////RENDER ENTITIES HERE////

	if (sceneOne != nullptr)
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