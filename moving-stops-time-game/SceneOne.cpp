#include "SceneOne.h"

SceneOne::SceneOne() {

	collision = Collision::Instance();

	ground1 = new PhysicsObject("ground.png", false);
	ground2 = new PhysicsObject("ground.png", false);
	wall = new PhysicsObject("ground.png", false);
	platform = new PhysicsObject("ground.png", false);

	ground1->Scale(Vector2(2, 1));
	ground2->Scale(Vector2(2, 1));
	wall->Scale(Vector2(0.2f, 6));
	platform->Scale(Vector2(1, 0.5f));

	ground1->Position(Vector2(Graphics::SCREEN_WIDTH / 2 - 300, Graphics::SCREEN_HEIGHT / 2));
	ground2->Position(Vector2(Graphics::SCREEN_WIDTH / 2 + 300, Graphics::SCREEN_HEIGHT / 2));
	wall->Position(Vector2(200, 250));
	platform->Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2 - 50));

	ground1->Tag("Ground");
	ground2->Tag("Ground");
	wall->Tag("Ground");
	platform->Tag("Ground");

	collision->AddCollider(ground1);
	collision->AddCollider(ground2);
	collision->AddCollider(wall);
	collision->AddCollider(platform);

	player = new Player();
	player->Position(player->GetPosition() + 150 * VEC2_DOWN + 300 * VEC2_RIGHT);

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
	delete platform;
	platform = nullptr;

	collision->Clear();
}

void SceneOne::Update() {

	if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_ESCAPE)) {

		if (!player->IsActive())
			player->Active(true);
		else
			player->Active(false);
	}

	ground1->Update();
	ground2->Update();
	
	//if (player->IsMoving()) {
		
		if (platform->GetPosition().y <= 300.0f || platform->GetPosition().y >= 500.0f)
			platformDirection = -platformDirection;

		platform->Velocity(platformDirection * 100 * VEC2_DOWN);
		platform->Update();
	//}

	if (player->IsActive())
		player->Update();
}

void SceneOne::LateUpdate() {

	collision->ResolveCollisions();
	//player->LateUpdate();
}

void SceneOne::Render() {

	player->Render();
	ground1->Render();
	ground2->Render();
	wall->Render();
	platform->Render();
}