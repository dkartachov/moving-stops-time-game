#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(const char* fileName) {

	sprite = new Sprite(fileName);
	sprite->Parent(this);
	sprite->Position(VEC2_ZERO);

	box = new BoxCollider(sprite->GetRect().w, sprite->GetRect().h);
	box->Parent(this);
	box->Position(VEC2_ZERO);
}

PhysicsObject::PhysicsObject(int w, int h) {

	sprite = nullptr;

	box = new BoxCollider(w, h);
	box->Parent(this);
	box->Position(VEC2_ZERO);
}

PhysicsObject::~PhysicsObject() {

	if (sprite != nullptr)
		delete sprite;
	sprite = nullptr;

	delete box;
	box = nullptr;
}

void PhysicsObject::Update() {

	box->Update();
}

void PhysicsObject::Render() {

	sprite->Render();
}

BoxCollider* PhysicsObject::GetBox() {
	
	return box;
}

void PhysicsObject::Velocity(Vector2 v) {

	velocity = v;
	Translate(Timer::Instance()->DeltaTime() * velocity);
}

Vector2 PhysicsObject::GetVelocity() {
	
	return velocity;
}

