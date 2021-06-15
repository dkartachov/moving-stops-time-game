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

Camera::Camera() {

	w = Graphics::SCREEN_WIDTH;
	h = w * 9 / 16;
}

void Camera::Size(int width) {

	w = width;
	h = w * 9 / 16;
}