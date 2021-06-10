#include "Collision.h"

Collision::Collision() {

}

void Collision::AddCollider(BoxCollider* collider) {

	colliders.push_back(collider);
}

bool Collision::AABB(SDL_Rect A, SDL_Rect B) {

	if ( (A.x < B.x + B.w) &&
		 (A.x + A.w > B.x) &&
		 (A.y < B.y + B.h) &&
		 (A.y + A.h > B.y) )
		return true;

	return false;
}

std::vector<BoxCollider*> Collision::GetColliders() {
	
	return colliders;
}