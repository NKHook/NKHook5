#pragma once

#include "../../Util/NewFramework.h"
#include "CSprite.h"

#include <vector>

namespace NKHook5 {
	namespace Classes {
		class CCompoundSprite : public CSprite
		{
		public:
			overload_allocators

		public:
			CBasePositionableObject* N00001ABB; //0x0104
			char pad_0108[4]; //0x0108
			std::vector<CSprite*> sprites; //0x010C
			char pad_0118[48]; //0x0118
		public:
			virtual void* GetName() { return nullptr; };
		}; //Size: 0x0148

		static_assert(sizeof(CCompoundSprite) == 0x148);
	}
}