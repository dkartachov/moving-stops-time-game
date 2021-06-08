#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(const char* filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animDir)
	:Sprite(filename, x, y, w, h) {

	timer = Timer::Instance();

	startX = x;
	startY = y;

	this->frameCount = frameCount;
	this->animationSpeed = animationSpeed;
	timePerFrame = this->animationSpeed / frameCount;
	animationTimer = 0.0f;

	animationDirection = animDir;
	animationDone = false;
	wrapMode = loop;
}

void AnimatedSprite::WrapMode(WRAP_MODE mode) {
	wrapMode = mode;
}

void AnimatedSprite::Play() {

	if (!animationDone) {

		animationTimer += timer->DeltaTime();

		if (animationTimer >= animationSpeed) {

			if (wrapMode == loop) {
				animationTimer -= animationSpeed;
			}
			else {
				animationDone = true;
				animationTimer = animationSpeed - timePerFrame;
			}
		}

		if (animationDirection == horizontal)
			clipRect.x = startX + (int)(animationTimer / timePerFrame) * width;
		else
			clipRect.y = startY + (int)(animationTimer / timePerFrame) * height;
	}

}

