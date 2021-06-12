#include "Collision.h"
#include <algorithm>

Collision* Collision::instance = nullptr;

Collision* Collision::Instance() {

	if (instance == nullptr)
		instance = new Collision();

	return instance;
}

void Collision::Release() {

	delete instance;
	instance = nullptr;
}

Collision::Collision() {

}

Collision::~Collision() {

}

void Collision::Clear() {

	colliders.clear();
}

void Collision::Update() {

}

bool Collision::XCausesCollision(PhysicsObject* A, PhysicsObject* B) {

	float delT = Timer::Instance()->DeltaTime();

	bool hasCollision = AABB(A->GetBox()->GetBox(), B->GetBox()->GetBox());
	A->Position(Vector2(A->GetPosition().x - A->GetVelocity().x * delT, A->GetPosition().y));
	B->Position(Vector2(B->GetPosition().x - B->GetVelocity().x * delT, B->GetPosition().y));

	bool hadCollision = AABB(A->GetBox()->GetBox(), B->GetBox()->GetBox());
	A->Position(Vector2(A->GetPosition().x + A->GetVelocity().x * delT, A->GetPosition().y));
	B->Position(Vector2(B->GetPosition().x + B->GetVelocity().x * delT, B->GetPosition().y));

	return hasCollision && !hadCollision;
}

bool Collision::YCausesCollision(PhysicsObject* A, PhysicsObject* B) {

	float delT = Timer::Instance()->DeltaTime();

	bool hasCollision = AABB(A->GetBox()->GetBox(), B->GetBox()->GetBox());
	A->Position(Vector2(A->GetPosition().x, A->GetPosition().y - A->GetVelocity().y * delT));
	B->Position(Vector2(B->GetPosition().x, B->GetPosition().y - B->GetVelocity().y * delT));


	bool hadCollision = AABB(A->GetBox()->GetBox(), B->GetBox()->GetBox());
	A->Position(Vector2(A->GetPosition().x, A->GetPosition().y + A->GetVelocity().y * delT));
	B->Position(Vector2(B->GetPosition().x, B->GetPosition().y + B->GetVelocity().y * delT));

	return hasCollision && !hadCollision;
}

void Collision::ResolveCollisions() {

	for (auto &collider : colliders) {

		if (collider->IsDynamic()) {

			std::vector<PhysicsObject*> colls = colliders;
			colls.erase(std::remove(colls.begin(), colls.end(), collider), colls.end());

			for (auto &c : colls) {

				while (XCausesCollision(collider, c)) {

					int depth;

					if (collider->GetBox()->GetBox().x > c->GetBox()->GetBox().x)
						depth = c->GetBox()->GetBox().x + c->GetBox()->GetBox().w - collider->GetBox()->GetBox().x;
					else
						depth = -(collider->GetBox()->GetBox().x + collider->GetBox()->GetBox().w - c->GetBox()->GetBox().x);

					collider->Position(Vector2(collider->GetPosition().x + depth, collider->GetPosition().y));
					collider->Velocity(Vector2(0.0f, collider->GetVelocity().y));
				}

				while (YCausesCollision(collider, c)) {

					int depth;

					if (collider->GetBox()->GetBox().y < c->GetBox()->GetBox().y)
						depth = -(collider->GetBox()->GetBox().y + collider->GetBox()->GetBox().h - c->GetBox()->GetBox().y);
					else
						depth = c->GetBox()->GetBox().y + c->GetBox()->GetBox().h - collider->GetBox()->GetBox().y;
		
					collider->Position(Vector2(collider->GetPosition().x, collider->GetPosition().y + depth));
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

bool Collision::AllAABB(BoxCollider A, std::string tag) {

	for (auto &collider : colliders) {

		if (collider->GetTag() == tag) {

			if ((A.GetBox().x < collider->GetBox()->GetBox().x + collider->GetBox()->GetBox().w) &&
				(A.GetBox().x + A.GetBox().w > collider->GetBox()->GetBox().x) &&
				(A.GetBox().y < collider->GetBox()->GetBox().y + collider->GetBox()->GetBox().h) &&
				(A.GetBox().y + A.GetBox().h > collider->GetBox()->GetBox().y))
				return true;
		}
	}

	return false;
}

std::vector<PhysicsObject*> Collision::GetColliders() {
	
	return colliders;
}