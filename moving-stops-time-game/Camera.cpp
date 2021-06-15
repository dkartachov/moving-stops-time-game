#include "Camera.h"

Camera* Camera::instance = nullptr;

Camera* Camera::Instance() {

	if (instance == nullptr)
		instance = new Camera();
	return instance;
}

void Camera::Release() {

	delete instance;
	instance = nullptr;
}

int Camera::GetWidth() {
	
	return w;
}

int Camera::GetHeight() {

	return h;
}

Camera::Camera() {

	w = Graphics::SCREEN_WIDTH;
	h = w * 9 / 16;
}