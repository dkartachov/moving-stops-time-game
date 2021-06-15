#include "Text.h"

Text::Text(std::string text, std::string fontPath, int size, SDL_Color color) {

	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetText(text, fontPath, size, color);

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	renderRect.w = width;
	renderRect.h = height;
}

void Text::Render() {

	Vector2 pos = GetPosition(world);
	Vector2 scale = GetScale(world);

	renderRect.x = (int)(pos.x - width * scale.x * 0.5f);
	renderRect.y = (int)(pos.y - height * scale.y * 0.5f);
	renderRect.w = (int)(width * scale.x);
	renderRect.h = (int)(height * scale.y);

	graphics->DrawTexture(texture, NULL, &renderRect, GetRotation(world));
}