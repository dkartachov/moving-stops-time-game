#pragma once
#include <SDL.h>

class Timer {
public:
	static Timer* Instance();
	static void Release();

	Timer();

	float DeltaTime();
	float TimeScale();

	void TimeScale(float t);

	void Update();
	void Reset();
private:
	static Timer* instance;
	unsigned int startTicks, elapsedTicks;
	float deltaTime, timeScale;
};