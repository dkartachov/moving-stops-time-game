#include "SceneOne.h"

SceneOne::SceneOne() {

	collision = new Collision();

	ground = new Sprite("ground.png");
	ground1 = new Sprite("ground.png");
	platform = new Sprite("ground.png");

	ground->Scale(Vector2(2, 1));
	ground1->Scale(Vector2(2, 1));

	ground->Position(Vector2(Graphics::SCREEN_WIDTH / 2 - 300, Graphics::SCREEN_HEIGHT / 2));
	ground1->Position(Vector2(Graphics::SCREEN_WIDTH / 2 + 300, Graphics::SCREEN_HEIGHT / 2));
	
	platform->Scale(Vector2(1, 0.5f));
	platform->Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2 - 50));

	collision->AddCollider(ground);
	collision->AddCollider(ground1);
	collision->AddCollider(platform);

	player = new Player(collision);
	player->Position(player->GetPosition() + 150 * VEC2_DOWN + 300 * VEC2_LEFT);
}

SceneOne::~SceneOne() {

	delete player;
	player = nullptr;
	delete ground;
	ground = nullptr;
	delete ground1;
	ground = nullptr;
	delete platform;
	platform = nullptr;
	delete collision;
	collision = nullptr;
}

void SceneOne::Update() {

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
	platform->Render();
}