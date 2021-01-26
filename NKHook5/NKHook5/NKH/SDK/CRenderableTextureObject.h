#pragma once
#include "CBasePositionableObject.h"
#include <iostream>
using namespace std;
// Created with ReClass.NET 1.2 by KN4CK3R

class CRenderableTextureObject : public CBasePositionableObject
{
public:
	int CRenderableTextureObject_Start; //0x00A8
	char pad_00AC[20]; //0x00AC
	class CTexture* Texture; //0x00C0
	char pad_00C4[4]; //0x00C4

	virtual void GetMinX() {};
	virtual void GetMinY() {};
	virtual void GetMaxX() {};
	virtual void GetMaxY() {};
	virtual void GetMinXY() {};
	virtual void GetMaxXY() {};
	virtual void SetShader() {};
	virtual void SetTexture() {};
public:
	CRenderableTextureObject() : CBasePositionableObject() {
		cout << "Pre render obj" << endl;
		Constructor(this);
		cout << "post render obj" << endl;
	}
	void Constructor(CRenderableTextureObject* self);
}; //Size: 0x00C8