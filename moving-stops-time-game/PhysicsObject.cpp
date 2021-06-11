#include "PhysicsObject.h"

PhysicsObject::PhysicsObject(const char* fileName, bool dynamic) {

	this->dynamic = dynamic;

	sprite = new Sprite(fileName);
	sprite->Parent(this);
	sprite->Position(VEC2_ZERO);

	box = new BoxCollider(sprite->GetRect().w, sprite->GetRect().h);
	box->Parent(this);
	box->Position(VEC2_ZERO);
}

PhysicsObject::PhysicsObject(int w, int h, bool dynamic) {

	this->dynamic = dynamic;

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

void PhysicsObject::Dynamic(bool state) {
	
	dynamic = state;
}

bool PhysicsObject::IsDynamic() {

	return dynamic;
}

void PhysicsObject::Update() {

	if (dynamic)
		velocity.y += 300 * Timer::Instance()->DeltaTime();

	Translate(Timer::Instance()->DeltaTime() * velocity);

	box->Update();
}

void PhysicsObject::Render() {

	sprite->Render();
}

BoxCollider* PhysicsObject::GetBox() {
	
	return box;
}

void PhysicsObject::Position(Vector2 p) {

	GameEntity::Position(p);
	box->Update();
}

void PhysicsObject::Velocity(Vector2 v) {

	velocity = v;
}

Vector2 PhysicsObject::GetVelocity() {
	
	return velocity;
}

