#include "SceneOne.h"

SceneOne::SceneOne() : Scene(4000, 4000) {

	ground1 = new PhysicsObject("ground.png", false);
	platform = new PhysicsObject("ground.png", false);
	platform2 = new PhysicsObject("ground.png", false);

	ground1->Scale(Vector2(2, 1));
	platform->Scale(Vector2(1, 0.5f));
	platform2->Scale(Vector2(1, 0.5f));

	ground1->Position(Vector2(levelWidth / 2, levelHeight / 2));
	platform->Position(Vector2(levelWidth / 2 + 200, levelHeight / 2 - 200));
	platform2->Position(Vector2(levelWidth / 2 - 200, levelHeight / 2 - 200));

	ground1->Tag("Ground");
	platform->Tag("Platform");
	platform2->Tag("Platform");

	collision->AddCollider(ground1);
	collision->AddCollider(platform);
	collision->AddCollider(platform2);

	player = new Player();
	player->Position(Vector2(levelWidth / 2, levelHeight / 2 - 100));

	camera->Parent(player);
	camera->Position(VEC2_ZERO);

	collision->AddCollider(player);
}

SceneOne::~SceneOne() {

	delete player;
	player = nullptr;
	delete ground1;
	ground1 = nullptr;
	delete platform;
	platform = nullptr;
	delete platform2;
	platform2 = nullptr;
}

void SceneOne::Update() {

	ground1->Update();
	
	if (player->IsMoving()) {
		
		if (platform->GetPosition().x <= levelWidth / 2 - 250 || platform->GetPosition().x >= levelWidth / 2 + 250)
			platformDirection = -platformDirection;

		if (platform2->GetPosition().y <= levelHeight / 2 - 250 || platform2->GetPosition().y >= levelHeight / 2 + 250)
			platform2Direction = -platform2Direction;

		platform->Velocity(platformDirection * 100 * VEC2_RIGHT);
		platform2->Velocity(platform2Direction * 100 * VEC2_UP);
	}
	else {
		platform->Velocity(VEC2_ZERO);
		platform2->Velocity(VEC2_ZERO);
	}

	if (player->IsActive()) {
		player->Update();
		platform->Update();
		platform2->Update();
	}

	camera->Parent(player);
	camera->Position(VEC2_ZERO);

	if (camera->GetPosition().y - camera->GetHeight() / 2 < 0) {

		camera->Parent(nullptr);
		camera->Position(Vector2(camera->GetPosition().x, camera->GetHeight() / 2));
	}
	else if (camera->GetPosition().y + camera->GetHeight() / 2 > levelHeight) {

		camera->Parent(nullptr);
		camera->Position(Vector2(camera->GetPosition().x, levelHeight - camera->GetHeight() / 2));
	}
}

void SceneOne::Render() {

	player->Render();
	ground1->Render();
	platform->Render();
	platform2->Render();
}