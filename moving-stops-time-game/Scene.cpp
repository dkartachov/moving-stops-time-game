#include "Scene.h"

Scene::Scene(int levelWidth, int levelHeight) {

	this->levelWidth = levelWidth;
	this->levelHeight = levelHeight;

	collision = Collision::Instance();
	camera = Camera::Instance();

	camera->Position(Vector2(this->levelWidth / 2, this->levelHeight / 2));
}

Scene::~Scene() {

	camera->Release();
	camera = nullptr;

	collision->Clear();
	collision = nullptr;
}

void Scene::Update() {

}

void Scene::LateUpdate() {

	collision->ResolveCollisions();
}

void Scene::Render() {

	
}
