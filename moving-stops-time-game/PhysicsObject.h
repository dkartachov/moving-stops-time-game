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

	void GravityModifier(float value);

	void Update();
	void Render();

	BoxCollider* GetBox();

	void Position(Vector2 p);

	void Velocity(Vector2 v);
	Vector2 GetVelocity();

private:
	float g = 300.0f;
	float gModifier = 1.0f;
	bool dynamic;
	Sprite* sprite;
	BoxCollider* box;
	Vector2 velocity;
};