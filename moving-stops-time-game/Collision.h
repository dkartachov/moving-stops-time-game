#pragma once
#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include <map>

class Collision {
public:

	Collision();

	void AddCollider(Sprite* collider);

	Sprite* AABB(SDL_Rect A);
	std::map<Sprite*, bool> GetColliders(SDL_Rect A);
	static bool AABB(SDL_Rect A, SDL_Rect B);

private:
	std::vector<Sprite*> colliders;
	std::map<Sprite*, bool> collMap;
};