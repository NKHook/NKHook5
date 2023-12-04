#pragma once

#include "../../Util/NewFramework.h"
#include "CBasePositionableObject.h"

namespace NKHook5::Classes
{
	class CRenderableTextureObject : public CBasePositionableObject
	{
	public:
		overload_allocators

	public:
		char pad_00A8[32]; //0x00A8

	public:
		CRenderableTextureObject() {};

		virtual ~CRenderableTextureObject() {}

		virtual void GetMinX() {}
		virtual void GetMinY() {}
		virtual void GetMaxX() {}
		virtual void GetMaxY() {}
		virtual void GetMinXY() {}
		virtual void GetMaxXY() {}
		virtual void SetShader(int shaderId) {}
		virtual void SetTexture(class CTexture* pCTexture) {}
	};

	static_assert(sizeof(CRenderableTextureObject) == 0xC8);
} // namespace NKHook5::Classes