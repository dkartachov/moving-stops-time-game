#include "SceneOne.h"

SceneOne::SceneOne() {

	collision = new Collision();

	ground = new Sprite("ground.png");
	ground1 = new Sprite("ground.png");
	wall = new Sprite("ground.png");
	platform = new Sprite("ground.png");

	ground->Scale(Vector2(2, 1));
	ground1->Scale(Vector2(2, 1));
	wall->Scale(Vector2(0.2f, 6));
	platform->Scale(Vector2(1, 0.5f));

	ground->Position(Vector2(Graphics::SCREEN_WIDTH / 2 - 300, Graphics::SCREEN_HEIGHT / 2));
	ground1->Position(Vector2(Graphics::SCREEN_WIDTH / 2 + 300, Graphics::SCREEN_HEIGHT / 2));
	wall->Position(Vector2(200, 250));
	platform->Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2 - 50));

	collision->AddCollider(ground);
	collision->AddCollider(ground1);
	collision->AddCollider(wall);
	collision->AddCollider(platform);

	player = new Player(collision);
	player->Position(player->GetPosition() + 150 * VEC2_DOWN + 300 * VEC2_RIGHT);
}

SceneOne::~SceneOne() {

	delete player;
	player = nullptr;
	delete ground;
	ground = nullptr;
	delete ground1;
	ground = nullptr;
	delete wall;
	wall = nullptr;
	delete platform;
	platform = nullptr;
	delete collision;
	collision = nullptr;
}

void SceneOne::Update() {

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_ESCAPE)) {

		if (!player->IsActive())
			player->Active(true);
		else
			player->Active(false);
	}

	if (player->IsActive())
		player->Update();

	ground->Update();
	ground1->Update();
	
	if (player->IsMoving()) {
		
		if (platform->GetPosition().x <= 300 || platform->GetPosition().x >= 500.0f)
			platformDirection = -platformDirection;

		platform->Translate(platformDirection * 100 * Timer::Instance()->DeltaTime() * VEC2_RIGHT);
	}

	platform->Update();
}

void SceneOne::LateUpdate() {

	player->LateUpdate();
}

void SceneOne::Render() {

	player->Render();
	ground->Render();
	ground1->Render();
	wall->Render();
	platform->Render();
}