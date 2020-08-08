#pragma once
struct Vector2 {
	float x, y;
	float& getX() {
		return this->x;
	}
	float& getY() {
		return this->y;
	}
	void setX(float value) {
		x = value;
	}
	void setY(float value) {
		y = value;
	}

public:
	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

struct Vector3 {
	float x, y, z;
	float& getX() {
		return this->x;
	}
	float& getY() {
		return this->y;
	}
	float& getZ() {
		return this->z;
	}
	void setX(float value) {
		x = value;
	}
	void setY(float value) {
		y = value;
	}
	void setZ(float value) {
		z = value;
	}

public:
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};