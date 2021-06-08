#include "BoxCollider.h"

BoxCollider::BoxCollider(int w, int h) {

	width = w;
	height = h;
}

SDL_Rect BoxCollider::GetBox() {

	return box;
}

void BoxCollider::Update() {

	Vector2 pos = GetPosition(world);
	Vector2 scale = GetScale(world);

	box.x = (int)(pos.x - width * scale.x * 0.5f);
	box.y = (int)(pos.y - height * scale.y * 0.5f);
	box.w = (int)(width * scale.x);
	box.h = (int)(height * scale.y);
}