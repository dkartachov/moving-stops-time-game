#include "Sprite.h"

Sprite::Sprite(const char* filename) {

	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetTexture(filename);

	clipped = false;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	renderRect.w = width;
	renderRect.h = height;

	flipY = SDL_FLIP_NONE;
}

Sprite::Sprite(const char* filename, int x, int y, int w, int h) {

	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetTexture(filename);

	clipped = true;

	width = w;
	height = h;
	renderRect.w = width;
	renderRect.h = height;

	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = width;
	clipRect.h = height;
}

Sprite::Sprite(std::string text, std::string fontPath, int size, SDL_Color color) {

	graphics = Graphics::Instance();
	texture = AssetManager::Instance()->GetText(text, fontPath, size, color);

	clipped = false;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	renderRect.w = width;
	renderRect.h = height;
}

SDL_Rect Sprite::GetRect() {

	return renderRect;
}

void Sprite::FlipY(SDL_RendererFlip flipY) {

	this->flipY = flipY;
}

void Sprite::Render(RENDER_MODE mode) {

	Vector2 pos = GetPosition(world);
	Vector2 scale = GetScale(world);

	switch (mode) {

	case WORLD:

		renderRect.x = (int)(pos.x - width * scale.x * 0.5f);
		renderRect.y = (int)(pos.y - height * scale.y * 0.5f);
		break;

	case CAMERA:

		renderRect.x = (int)(pos.x - width * scale.x * 0.5f) - Camera::Instance()->GetPosition().x + Camera::Instance()->GetWidth() / 2;
		renderRect.y = (int)(pos.y - height * scale.y * 0.5f) - Camera::Instance()->GetPosition().y + Camera::Instance()->GetHeight() / 2;
		break;

	default:
		break;
	}

	renderRect.w = (int)(width * scale.x);
	renderRect.h = (int)(height * scale.y);
	
	graphics->DrawTexture(texture, clipped ? &clipRect : NULL, &renderRect, GetRotation(world), flipY);
}