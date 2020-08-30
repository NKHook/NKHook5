#pragma once
#include "../NMath.h"
#include "CMatrix.h"
// Created with ReClass.NET 1.2 by KN4CK3R

class CBasePositionableObject
{
public:
	char pad_0000[8]; //0x0000
	int onei; //0x000C
	class CBasePositionableObject* parentObject; //0x0010
	void* selfPlus14; //0x0014
	void* selfPlus14_2; //0x0018
	char pad_001C[4]; //0x001C
	float Width; //0x0020
	float Height; //0x0024
	class CMatrix CMatrix; //0x0028
	Vector3 Pos;
	float onef; //0x0074
	char pad_0078[24]; //0x0078
	float AlignmentX; //0x0090
	float AlignmentY; //0x0094
	char pad_0098[4]; //0x0098
	float Angle; //0x009C
	float ScaleX; //0x00A0
	float ScaleY; //0x00A4

	virtual void Function0() {};
	virtual void Draw(bool drawChildren) {};
	virtual void DrawOverlay() {};
	virtual void Process_r() {};
	virtual void HitTest() {};
	virtual void DeleteChildren() {};
	virtual void SetXYZ(float x, float y, float z) {};
	virtual void SetXY(float x, float y) {};
	virtual void SetXYB(float x, float y) {};
	virtual void SetX(float x) {};
	virtual void SetY(float y) {};
	virtual void SetZ(float z) {};
	virtual void MoveXYZ(float x, float y, float z) {};
	virtual void MoveXY(float x, float y) {};
	virtual void MoveX(float x) {};
	virtual void MoveY(float y) {};
	virtual void MoveZ(float z) {};
	virtual void SetScale(float x, float y) {};
	virtual void SetScaleB(float x, float y) {};
	virtual void SetScaleX(float x) {};
	virtual void SetScaleY(float y) {};
	virtual void SetAngle(float angle) {};
	virtual void SetWH(float width, float height) {};
	virtual void SetW(float width) {};
	virtual void SetH(float height) {};
	virtual void SetAlignmentX(float x) {};
	virtual void SetAlignmentY(float y) {};
	virtual void SetAlignmentXY(float x, float y) {};
	virtual void GetXYZ(Vector3* xyz) {};
	virtual void GetXY(Vector2* xy) {};
	virtual void GetX(float* x) {};
	virtual void GetY(float* y) {};
	virtual void GetZ(float* z) {};
	virtual void GetWH(Vector2* wh) {};
	virtual void GetW(float* w) {};
	virtual void GetH(float* h) {};
	virtual void UpdateLocalTransform() {};
	virtual void UpdateTransform() {};
	virtual void UpdateTransform_r() {};
	virtual void ForceUpdate() {};
	virtual void SetScreenTransition() {};
	virtual void SetDefaultDirtyState() {};
	virtual void _DeleteChildrenInternal() {};
	virtual void BaseDrawChildren() {};

public:
	CBasePositionableObject() {
		Constructor(this);
	}
	Vector3& getPosition() {
		Vector3* thePos = new Vector3();
		this->GetXYZ(thePos);
		return *thePos;
	}
	void Constructor(CBasePositionableObject* self);
}; //Size: 0x00C0