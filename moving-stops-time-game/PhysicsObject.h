#pragma once
#include "Sprite.h"
#include "BoxCollider.h"
#include "Timer.h"

class PhysicsObject : public GameEntity {

public:
	PhysicsObject(const char* fileName, bool dynamic = true);
	PhysicsObject(int w, int h, bool dynamic = true);

	~PhysicsObject();

	void Dynamic(bool state);
	bool IsDynamic();

	void Update();
	void Render();

	BoxCollider* GetBox();

	void Position(Vector2 p);

	void Velocity(Vector2 v);
	Vector2 GetVelocity();

private:
	bool dynamic;
	Sprite* sprite;
	BoxCollider* box;

	Vector2 velocity;
};