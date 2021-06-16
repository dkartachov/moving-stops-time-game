#include "SceneOne.h"

SceneOne::SceneOne() : Scene(3000, Graphics::SCREEN_HEIGHT) {

	ground1 = new PhysicsObject("ground.png", false);
	ground2 = new PhysicsObject("ground.png", false);

	wall = new PhysicsObject("ground.png", false);

	platform1 = new PhysicsObject("ground.png", false);

	wall->Scale(Vector2(0.2, 22));
	wall->Update();
	ground1->Scale(Vector2(3, 1));
	ground1->Update();
	ground2->Scale(Vector2(3, 1));
	ground2->Update();
	platform1->Scale(Vector2(1, 0.5f));

	wall->Position(Vector2(0, levelHeight / 2));

	ground1->Position(Vector2(100, 2 * levelHeight / 3));
	ground2->Position(Vector2(camera->GetWidth() - 100, 2 * levelHeight / 3));

	platform1->Position(Vector2(camera->GetWidth() / 2, 2 * levelHeight / 3 ));

	ground1->Tag("Ground");
	ground2->Tag("Ground");
	platform1->Tag("Platform");

	collision->AddCollider(ground1);
	collision->AddCollider(ground2);
	collision->AddCollider(wall);
	collision->AddCollider(platform1);

	player = new Player();
	player->Position(Vector2(ground1->GetPosition().x, levelHeight / 2 - 100));

	camera->Parent(player);
	camera->Position(VEC2_ZERO);

	collision->AddCollider(player);
}

SceneOne::~SceneOne() {

	delete player;
	player = nullptr;
	delete ground1;
	ground1 = nullptr;
	delete ground2;
	ground2 = nullptr;
	delete wall;
	wall = nullptr;
	delete platform1;
	platform1 = nullptr;
}

void SceneOne::Update() {

	ground1->Update();
	ground2->Update();
	wall->Update();
	
	if (player->IsMoving()) {
		
		if (platform1->GetPosition().y <= 2 * levelHeight / 3 - 100 || platform1->GetPosition().y >= 2 * levelHeight / 3 + 100)
			platformDirection = -platformDirection;

		platform1->Velocity(platformDirection * 190 * VEC2_UP);
	}
	else {

		platform1->Velocity(VEC2_ZERO);
	}

	if (player->IsActive()) {

		player->Update();
		platform1->Update();
	}

	camera->Parent(player);
	camera->Position(VEC2_ZERO);

	if (camera->GetPosition().x - camera->GetWidth() / 2 < 0) {

		camera->Parent(nullptr);
		camera->Position(Vector2(camera->GetWidth() / 2, camera->GetPosition().y));
	}
	else if (camera->GetPosition().x + camera->GetWidth() / 2 > levelWidth) {

		camera->Parent(nullptr);
		camera->Position(Vector2(levelWidth - camera->GetWidth() / 2, camera->GetPosition().y));
	}

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
	ground2->Render();
	wall->Render();
	platform1->Render();
}