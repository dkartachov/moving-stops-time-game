#pragma once
#include "Timer.h"
#include "Sprite.h"

class AnimatedSprite : public Sprite {
public:
	enum WRAP_MODE { once = 0, loop = 1 };
	enum ANIM_DIR { horizontal = 0, vertical = 1 };
public:
	AnimatedSprite(const char* filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animDir = horizontal);
	void WrapMode(WRAP_MODE mode);

	void Play();
private:
	Timer* timer;
	int startX, startY;
	int frameCount;
	float animationTimer, animationSpeed, timePerFrame;

	WRAP_MODE wrapMode;
	ANIM_DIR animationDirection;
	bool animationDone;
};