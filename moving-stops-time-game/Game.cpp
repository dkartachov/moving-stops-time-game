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

	mainMenu = new MainMenu();

	pauseMenu = new PauseMenu();
	pauseMenu->Active(false);

	levelOne = new LevelOne();
	levelOne->Active(false);

	player = new Player();
}

void Game::EarlyUpdate() {
	timer->Reset();
	inputManager->Update();
}

void Game::Update() {

	////GAME ENTITY UPDATES HERE////
	
	mainMenu->Update();

	if (mainMenu->Quit())
		quit = true;
	if (mainMenu->NewGame())
		levelOne->Active(true);

	levelOne->Update(pauseMenu, player);
		
	pauseMenu->Update(mainMenu);

	if (pauseMenu->Quit())
		quit = true;

	///////////////////////////////
}

void Game::LateUpdate() {

	////COLLISION DETECTION HERE////



	///////////////////////////////

	inputManager->UpdatePreviousInput();
}

void Game::Render() {

	graphics->Clear();

	////RENDER ENTITIES HERE////

	mainMenu->Render();

	levelOne->Render(player);

	pauseMenu->Render();
		
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