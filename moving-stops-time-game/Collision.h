#pragma once
#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "BoxCollider.h"

class Collision {
public:

	Collision();

	void PlayerCollision();

	void AddCollider(BoxCollider* collider);

	Sprite* AABB(SDL_Rect A);
	std::vector<BoxCollider*> GetColliders();
	static bool AABB(SDL_Rect A, SDL_Rect B);

private:
	std::vector<BoxCollider*> colliders;
	std::map<Sprite*, bool> collMap;
};