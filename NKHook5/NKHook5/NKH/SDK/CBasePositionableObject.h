#pragma once
#include "CMatrix.h"
// Created with ReClass.NET 1.2 by KN4CK3R

class CBasePositionableObject
{
public:
	char pad_0004[12]; //0x0004
	class CBasePositionableObject* parentObject; //0x0010
	char pad_0014[12]; //0x0014
	float Width; //0x0020
	float Height; //0x0024
	CMatrix CMatrix; //0x0028
	float PosX; //0x0068
	float PosY; //0x006C
	float PosZ; //0x0070
	char pad_0074[28]; //0x0074
	float AlignmentX; //0x0090
	float AlignmentY; //0x0094
	char pad_0098[4]; //0x0098
	float Angle; //0x009C

	virtual void Function0();
	virtual void Draw(bool);
	virtual void DrawOverlay();
	virtual void Process_r();
	virtual void Function4();
	virtual void DeleteChildren();
	virtual void SetXYZ();
	virtual void SetXY();
	virtual void SetXY(void*);
	virtual void SetX();
	virtual void SetY();
	virtual void SetZ();
	virtual void MoveXYZ();
	virtual void MoveXY();
	virtual void MoveX();
	virtual void MoveY();
	virtual void MoveZ();
	virtual void SetScale();
	virtual void SetScale(void*);
	virtual void SetScaleX();
	virtual void SetScaleY();
	virtual void SetAngle(float angle);
	virtual void SetWH();
	virtual void SetW();
	virtual void SetH();
	virtual void SetAlignmentX();
	virtual void SetAlignmentY();
	virtual void SetAlignmentXY();
	virtual void GetXYZ();
	virtual void GetXY();
	virtual void GetX();
	virtual void GetY();
	virtual void GetZ();
	virtual void GetWH();
	virtual void GetW();
	virtual void GetH();
	virtual void Function36();
	virtual void Function37();
	virtual void Function38();
	virtual void Function39();
	virtual void SetScreenTransition();
	virtual void SetDefaultDirtyState();
	virtual void Function42();
	virtual void BaseDrawChildren();


}; //Size: 0x00C0