#include "Collision.h"
#include <algorithm>

Collision::Collision() {

}

void Collision::Update() {

}

bool Collision::XCausesCollision(PhysicsObject* A, PhysicsObject* B) {

	float delT = Timer::Instance()->DeltaTime();

	bool hasCollision = AABB(A->GetBox()->GetBox(), B->GetBox()->GetBox());
	A->Position(Vector2(A->GetPosition().x - A->GetVelocity().x * delT, A->GetPosition().y));
	bool hadCollision = AABB(A->GetBox()->GetBox(), B->GetBox()->GetBox());
	A->Position(Vector2(A->GetPosition().x + A->GetVelocity().x * delT, A->GetPosition().y));

	return hasCollision && !hadCollision;
}

bool Collision::YCausesCollision(PhysicsObject* A, PhysicsObject* B) {

	float delT = Timer::Instance()->DeltaTime();

	bool hasCollision = AABB(A->GetBox()->GetBox(), B->GetBox()->GetBox());
	A->Position(Vector2(A->GetPosition().x, A->GetPosition().y - A->GetVelocity().y * delT));
	bool hadCollision = AABB(A->GetBox()->GetBox(), B->GetBox()->GetBox());
	A->Position(Vector2(A->GetPosition().x, A->GetPosition().y + A->GetVelocity().y * delT));

	

	return hasCollision && !hadCollision;
}

void Collision::ResolveCollisions() {

	for (auto &collider : colliders) {

		if (collider->IsDynamic()) {

			std::vector<PhysicsObject*> colls = colliders;
			colls.erase(std::remove(colls.begin(), colls.end(), collider), colls.end());

			for (auto &c : colls) {

				while (XCausesCollision(collider, c)) {

					collider->Position(Vector2(collider->GetPosition().x - collider->GetVelocity().x * Timer::Instance()->DeltaTime(), collider->GetPosition().y));
					collider->Velocity(Vector2(0.0f, collider->GetVelocity().y));
				}

				while (YCausesCollision(collider, c)) {

					collider->Position(Vector2(collider->GetPosition().x, collider->GetPosition().y - collider->GetVelocity().y * Timer::Instance()->DeltaTime()));
					collider->Velocity(Vector2(collider->GetVelocity().x, 0.0f));
				}
			}
		}
	}
}

void Collision::AddCollider(PhysicsObject* collider) {

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

std::vector<PhysicsObject*> Collision::GetColliders() {
	
	return colliders;
}