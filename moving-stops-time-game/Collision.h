#pragma once
#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "PhysicsObject.h"

class Collision {
public:

	Collision();

	void Update();

	void PlayerCollision();

	void AddCollider(PhysicsObject* collider);

	Sprite* AABB(SDL_Rect A);
	std::vector<PhysicsObject*> GetColliders();
	static bool AABB(SDL_Rect A, SDL_Rect B);

private:
	std::vector<PhysicsObject*> colliders;
};