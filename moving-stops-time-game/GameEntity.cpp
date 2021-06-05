#include "GameEntity.h"

GameEntity::GameEntity(float x, float y) {
	position.x = x;
	position.y = y;

	rotation = 0.0f;

	active = true;
	parent = NULL;

	scale = VEC2_ONE;
}

void GameEntity::Position(Vector2 pos) {
	position = pos;
}

Vector2 GameEntity::GetPosition(SPACE space) {

	if (space == local || parent == NULL)
		return position;

	Vector2 parentScale = parent->GetScale(world);
	Vector2 scaledPosition = Vector2(position.x * parentScale.x, position.y * parentScale.y);
	Vector2 rotPos = RotateVector(scaledPosition, parent->GetRotation(local));

	return parent->GetPosition(world) + rotPos;
}

void GameEntity::Rotation(float angle) {
	rotation = angle;

	if (rotation > 360.0f)
		rotation -= 360.0f;
	if (rotation < 0.0f)
		rotation += 360.0f;
}

float GameEntity::GetRotation(SPACE space) {
	if (space == local || parent == NULL)
		return rotation;
	return parent->GetRotation(world) + rotation;
}

void GameEntity::Scale(Vector2 scale) {
	this->scale = scale;
}

Vector2 GameEntity::GetScale(SPACE space) {

	if (space == local || parent == NULL)
		return scale;

	Vector2 parentScale = parent->GetScale(world);
	parentScale.x *= scale.x;
	parentScale.y *= scale.y;

	return parentScale;
}

void GameEntity::Active(bool state) {
	active = state;
}

bool GameEntity::IsActive() {
	return active;
}

void GameEntity::Parent(GameEntity* parent) {

	if (parent == NULL) {

		position = GetPosition(world);
		rotation = GetRotation(world);
		scale = GetScale(world);
	}
	else {

		if (this->parent != NULL)
			Parent(NULL);

		Vector2 parentScale = parent->GetScale(world);
		Vector2 delta = GetPosition(world) - parent->GetPosition(world);

		position = RotateVector(delta, -parent->GetRotation(world));
		position.x /= parentScale.x;
		position.y /= parentScale.y;

		rotation -= parent->GetRotation(world);

		scale = Vector2(scale.x / parentScale.x, scale.y / parentScale.y);
	}

	this->parent = parent;
}

GameEntity* GameEntity::GetParent() {
	return parent;
}

void GameEntity::Translate(Vector2 vec) {
	position += vec;
}

void GameEntity::Rotate(float angle) {
	rotation -= angle;
}

void GameEntity::Update() {

}

void GameEntity::Render() {

}