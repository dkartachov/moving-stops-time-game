#pragma once
#include <math.h>

constexpr auto PI = 3.14159265;
constexpr auto DEG_TO_RAD = PI / 180.0f;

struct Vector2 {
	float x, y;

	Vector2(float _x = 0.0f, float _y = 0.0f) : x(_x), y(_y) {}

	float MagnitudeSquared() { return x * x + y * y; }
	float Magnitude() { return (float)sqrt(MagnitudeSquared()); }

	Vector2 Normalize() {
		float magnitude = Magnitude();
		return Vector2(x / magnitude, y / magnitude);
	}

	inline Vector2 operator *=(const float& c) {
		x = c * x;
		y = c * y;
		return Vector2(x, y);
	}

	inline Vector2 operator +(const Vector2& vec) {
		return Vector2(x + vec.x, y + vec.y);
	}

	inline Vector2 operator -(const Vector2& vec) {
		return Vector2(x - vec.x, y - vec.y);
	}

	inline Vector2 operator +=(const Vector2& vec) {
		x += vec.x;
		y += vec.y;
		return Vector2(x, y);
	}

	inline Vector2 operator -=(const Vector2& vec) {
		x -= vec.x;
		y -= vec.y;
		return Vector2(x, y);
	}
};

inline Vector2 operator *(const float& c, const Vector2& vec) {
	return Vector2(c * vec.x, c * vec.y);
}

inline Vector2 RotateVector(Vector2& vec, float angle) {
	angle *= DEG_TO_RAD;
	return Vector2(vec.x * cos(angle) - vec.y * sin(angle), vec.x * sin(angle) + vec.y * cos(angle));
}

const Vector2 VEC2_ZERO = { 0.0f, 0.0f };
const Vector2 VEC2_ONE = { 1.0f, 1.0f };
const Vector2 VEC2_UP = { 0.0f, 1.0f };
const Vector2 VEC2_DOWN = { 0.0f, -1.0f };
const Vector2 VEC2_RIGHT = { 1.0f, 0.0f };
const Vector2 VEC2_LEFT = { -1.0f, 0.0f };