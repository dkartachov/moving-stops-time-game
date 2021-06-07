#include "Collision.h"

bool Collision::AABB(SDL_Rect A, SDL_Rect B) {

	if ( (A.x < B.x + B.w) &&
		 (A.x + A.w > B.x) &&
		 (A.y < B.y + B.h) &&
		 (A.y + A.h > B.y) )
		return true;

	return false;
}