#include "Collision.h"

Collision::Collision() {

}

void Collision::AddCollider(Sprite* collider) {

	colliders.push_back(collider);
	
	for (auto coll : colliders) {
		collMap[coll] = false;
	}
}

bool Collision::AABB(SDL_Rect A, SDL_Rect B) {

	if ( (A.x < B.x + B.w) &&
		 (A.x + A.w > B.x) &&
		 (A.y < B.y + B.h) &&
		 (A.y + A.h > B.y) )
		return true;

	return false;
}

Sprite* Collision::AABB(SDL_Rect A) {

	for (auto colls : colliders) {

		if ((A.x < colls->GetRect().x + colls->GetRect().w) &&
			(A.x + A.w > colls->GetRect().x) &&
			(A.y < colls->GetRect().y + colls->GetRect().h) &&
			(A.y + A.h > colls->GetRect().y)) {
			
			return colls;
		}
	}

	return nullptr;
}

void Collision::GetColliders(SDL_Rect A) {

	for (auto x : collMap) {
		printf("%d ", x.second);
	}
	printf("\n");
}