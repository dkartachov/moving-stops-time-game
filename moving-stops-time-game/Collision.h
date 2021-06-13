#pragma once
#include <SDL.h>
#include <vector>
#include "Sprite.h"
#include "PhysicsObject.h"

class Collision {
public:

	static Collision* Instance();
	static void Release();

	Collision();
	~Collision();

	void Clear();

	void Update();

	bool XCausesCollision(PhysicsObject* A, PhysicsObject* B);
	bool YCausesCollision(PhysicsObject* A, PhysicsObject* B);
	void ResolveCollisions();

	void AddCollider(PhysicsObject* collider);

	std::vector<PhysicsObject*> GetColliders();
	PhysicsObject* GetCurrentCollider();

	static bool AABB(SDL_Rect A, SDL_Rect B);
	bool AllAABB(BoxCollider A, std::vector<std::string> tags);

private:
	static Collision* instance;
	std::vector<PhysicsObject*> colliders;
	PhysicsObject* currentCollider;
};