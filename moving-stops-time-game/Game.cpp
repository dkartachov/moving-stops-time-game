#include "Game.h"

Game::Game() {

	quit = false;

	timer = Timer::Instance();
	graphics = Graphics::Instance();
	assetManager = AssetManager::Instance();
	inputManager = InputManager::Instance();
	audioManager = AudioManager::Instance();
	collision = Collision::Instance();

	mainMenu = new MainMenu();
	//sceneOne = new SceneOne();
}

Game::~Game() {

	delete mainMenu;
	mainMenu = nullptr;

	delete sceneOne;
	sceneOne = nullptr;

	Timer::Release();
	timer = nullptr;

	AssetManager::Release();
	assetManager = nullptr;

	InputManager::Release();
	inputManager = nullptr;

	AudioManager::Release();
	audioManager = nullptr;

	Collision::Release();
	collision = nullptr;

	Graphics::Release();
	graphics = nullptr;

	Camera::Release();
	camera = nullptr;
}

void Game::EarlyUpdate() {

	timer->Reset();
	inputManager->Update();
}

void Game::Update() {

	////GAME ENTITY UPDATES HERE////

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_ESCAPE)) {
		delete sceneOne;
		sceneOne = nullptr;
		mainMenu = new MainMenu();
	}

	if (mainMenu != nullptr) {

		mainMenu->Update();

		if (mainMenu->NewGame()) {

			delete mainMenu;
			mainMenu = nullptr;
			sceneOne = new SceneOne();
		}
		else if (mainMenu->QuitGame()) {

			quit = true;
		}	
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

	if (mainMenu != nullptr)
		mainMenu->Render();

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

		//printf("%f\n", timer->DeltaTime());

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