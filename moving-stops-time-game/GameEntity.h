#pragma once
#include "Mathematics.h"
#include <string>

class GameEntity {
public:
	enum SPACE { local = 0, world = 1 };
public:
	GameEntity(float x = 0.0f, float y = 0.0f);

	void Tag(std::string name);
	std::string GetTag();

	void Position(Vector2 position);
	Vector2 GetPosition(SPACE space = world);

	void Rotation(float angle);
	float GetRotation(SPACE space = world);

	void Scale(Vector2 scale);
	Vector2 GetScale(SPACE space = world);

	void Active(bool active);
	bool IsActive();

	void Parent(GameEntity* parent);
	GameEntity* GetParent();

	void Translate(Vector2 vec);
	void Rotate(float angle);

	virtual void Update();
	virtual void Render();
private:
	std::string tag;
	Vector2 position;
	float rotation;
	Vector2 scale;
	bool active;
	GameEntity* parent;
};
