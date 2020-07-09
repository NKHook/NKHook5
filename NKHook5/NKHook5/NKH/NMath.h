#pragma once
struct Vector2 {
	union {
		float x, y;
	};
	float& getX() {
		return this->x;
	}
	float& getY() {
		return this->y;
	}
};