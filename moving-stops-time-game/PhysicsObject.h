#pragma once
#include "Sprite.h"
#include "BoxCollider.h"
#include "Timer.h"

class PhysicsObject : public GameEntity {

public:

	PhysicsObject(const char* fileName);
	PhysicsObject(int w, int h);

	~PhysicsObject();

	void Update();
	void Render();

	BoxCollider* GetBox();

	void Velocity(Vector2 v);
	Vector2 GetVelocity();

private:
	Sprite* sprite;
	BoxCollider* box;

	Vector2 velocity;
};