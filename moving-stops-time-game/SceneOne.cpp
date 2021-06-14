#include "SceneOne.h"

SceneOne::SceneOne() {

	collision = Collision::Instance();

	ground1 = new PhysicsObject("ground.png", false);
	platform = new PhysicsObject("ground.png", false);
	platform2 = new PhysicsObject("ground.png", false);

	ground1->Scale(Vector2(2, 1));
	platform->Scale(Vector2(1, 0.5f));
	platform2->Scale(Vector2(1, 0.5f));

	ground1->Position(Vector2(Graphics::SCREEN_WIDTH / 2 - 300, Graphics::SCREEN_HEIGHT / 2));
	platform->Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2 - 50));
	platform2->Position(Vector2(Graphics::SCREEN_WIDTH / 2 + 300, Graphics::SCREEN_HEIGHT / 2));

	ground1->Tag("Ground");
	platform->Tag("Platform");
	platform2->Tag("Platform");

	collision->AddCollider(ground1);
	collision->AddCollider(platform);
	collision->AddCollider(platform2);

	player = new Player();
	player->Position(player->GetPosition() + 150 * VEC2_DOWN + 300 * VEC2_LEFT);

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

	collision->Clear();
}

void SceneOne::Update() {

	ground1->Update();
	
	if (player->IsMoving()) {
		
		if (platform->GetPosition().x <= 500 || platform->GetPosition().x >= 700.0f)
			platformDirection = -platformDirection;

		if (platform2->GetPosition().y <= 300.0f || platform2->GetPosition().y >= 500.0f)
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
		
}

void SceneOne::LateUpdate() {

	collision->ResolveCollisions();
}

void SceneOne::Render() {

	player->Render();
	ground1->Render();
	platform->Render();
	platform2->Render();
}