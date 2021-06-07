#include "SceneOne.h"

SceneOne::SceneOne() {

	player = new Player();
	ground = new Sprite("ground.png");

	ground->Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
	ground->Scale(Vector2(5, 1));
	player->Position(player->GetPosition() + 400 * VEC2_DOWN);

}

SceneOne::~SceneOne() {

	delete player;
	player = NULL;
}

void SceneOne::Update() {

	player->Update();
	ground->Update();
}

void SceneOne::LateUpdate() {

	if (Collision::AABB(player->GetRect(), ground->GetRect())) {
		printf("Collision detected\n");
		player->LateUpdate();
	}	
	else
		printf("No collision\n");
}

void SceneOne::Render() {

	player->Render();
	ground->Render();
}