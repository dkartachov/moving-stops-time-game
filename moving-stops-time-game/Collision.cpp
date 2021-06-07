#include "Collision.h"

bool Collision::AABB(SDL_Rect A, SDL_Rect B) {

	if (A.x + A.w > B.x &&
		A.x < B.x + B.w &&
		A.y + A.h > B.y &&
		A.y < B.y + B.h)
		return true;

	return false;
}