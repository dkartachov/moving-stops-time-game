#include "SceneOne.h"

SceneOne::SceneOne() {

	player = new Player();
	printf("player position: (%f, %f)", player->GetPosition().x, player->GetPosition().y);

	ground = new Sprite("ground.png");
	ground->Position(Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 2));
	player->Position(player->GetPosition() + 200 * VEC2_DOWN);
}

SceneOne::~SceneOne() {

	delete player;
	player = NULL;
}

void SceneOne::Update() {

	player->Update();
	ground->Update();
}

void SceneOne::Render() {

	player->Render();
	ground->Render();
}