#pragma once
#include "CMatrix.h"
// Created with ReClass.NET 1.2 by KN4CK3R

class CBasePositionableObject
{
public:
	char pad_0000[12]; //0x0000
	int32_t onei; //0x000C
	class CBasePositionableObject* parentObject; //0x0010
	char pad_0014[12]; //0x0014
	float Width; //0x0020
	float Height; //0x0024
	class CMatrix CMatrix; //0x0028
	float PosX; //0x0068
	float PosY; //0x006C
	float PosZ; //0x0070
	float onef; //0x0074
	char pad_0078[16]; //0x0078
	int32_t nine; //0x0088
	char pad_008C[4]; //0x008C
	float AlignmentX; //0x0090
	float AlignmentY; //0x0094
	char pad_0098[4]; //0x0098
	float Angle; //0x009C
	float oneone[2]; //0x00A0

	virtual void Function0() {};
	virtual void Draw(bool) {};
	virtual void DrawOverlay() {};
	virtual void Process_r() {};
	virtual void Function4() {};
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
	virtual void GetXYZ(float* xyz) {};
	virtual void GetXY(float* xy) {};
	virtual void GetX(float* x) {};
	virtual void GetY(float* y) {};
	virtual void GetZ(float* z) {};
	virtual void GetWH(float* wh) {};
	virtual void GetW(float* w) {};
	virtual void GetH(float* h) {};
	virtual void Function36() {};
	virtual void Function37() {};
	virtual void Function38() {};
	virtual void Function39() {};
	virtual void SetScreenTransition() {};
	virtual void SetDefaultDirtyState() {};
	virtual void Function42() {};
	virtual void BaseDrawChildren() {};

public:
	CBasePositionableObject() {
		int vTableAddr = Utils::getModuleBase() + 0x72F25C; // "BTD5-Win.exe"+72F25C 
		memcpy(this, &vTableAddr, 4);
		onei = 1;
		this->CMatrix = CMatrix::CMatrix(1);
		onef = 1;
		nine = 9;
		oneone[0] = 1;
		oneone[1] = 1;
	}
}; //Size: 0x00C0