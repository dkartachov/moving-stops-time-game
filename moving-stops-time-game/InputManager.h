#pragma once
#include <SDL.h>
#include <string.h>
#include "Mathematics.h"

class InputManager {
public:
	enum MOUSE_BUTTON { left = 0, right, middle, back, forward };
public:
	static InputManager* Instance();
	static void Release();

	InputManager();
	~InputManager();

	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	bool MouseButtonDown(MOUSE_BUTTON button);
	bool MouseButtonPressed(MOUSE_BUTTON button);
	bool MouseButtonReleased(MOUSE_BUTTON button);

	Vector2 MousePosition();

	void Update();
	void UpdatePreviousInput();
private:
	static InputManager* instance;
	
	Uint8* prevKeyboardState;
	const Uint8* keyboardState;
	int keyLength;

	Uint32 prevMouseState;
	Uint32 mouseState;
	int mouseX, mouseY;
};