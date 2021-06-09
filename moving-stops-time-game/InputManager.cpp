#include "InputManager.h"

InputManager* InputManager::instance = NULL;

InputManager* InputManager::Instance() {
	if (instance == NULL)
		instance = new InputManager();
	return instance;
}

void InputManager::Release() {
	delete instance;
	instance = NULL;
}

InputManager::InputManager() {

	keyboardState = SDL_GetKeyboardState(&keyLength);
	prevKeyboardState = new Uint8[keyLength];
	memcpy(prevKeyboardState, keyboardState, keyLength);
}

InputManager::~InputManager() {
	delete[] prevKeyboardState;
	prevKeyboardState = nullptr;
	keyboardState = nullptr;
}

bool InputManager::KeyDown(SDL_Scancode scanCode) {
	return keyboardState[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scanCode) {
	return !prevKeyboardState[scanCode] && keyboardState[scanCode];
}

bool InputManager::KeyReleased(SDL_Scancode scanCode) {
	return prevKeyboardState[scanCode] && !keyboardState[scanCode];
}

Vector2 InputManager::MousePosition() {
	return Vector2((float)mouseX, (float)mouseY);
}

bool InputManager::MouseButtonDown(MOUSE_BUTTON button) {
	
	Uint32 mask = 0;
	
	switch (button) {
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (mouseState & mask);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTON button) {

	Uint32 mask = 0;

	switch (button) {
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return !(prevMouseState & mask) && (mouseState & mask);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTON button) {

	Uint32 mask = 0;

	switch (button) {
	case left:
		mask = SDL_BUTTON_LMASK;
		break;
	case right:
		mask = SDL_BUTTON_RMASK;
		break;
	case middle:
		mask = SDL_BUTTON_MMASK;
		break;
	case back:
		mask = SDL_BUTTON_X1MASK;
		break;
	case forward:
		mask = SDL_BUTTON_X2MASK;
		break;
	}

	return (prevMouseState & mask) && !(mouseState & mask);
}

void InputManager::Update() {
	mouseState = SDL_GetMouseState(&mouseX, &mouseY);
}

void InputManager::UpdatePreviousInput() {

	memcpy(prevKeyboardState, keyboardState, keyLength);
	prevMouseState = mouseState;
}