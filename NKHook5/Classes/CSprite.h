#pragma once

#include "../../Util/NewFramework.h"
#include "CRenderableTextureObject.h"

namespace NKHook5 {
	namespace Classes {
		class CSprite : public CRenderableTextureObject {
		public:
			overload_new

		public:
			char pad_00C8[60]; //0x00C8

		public:
			virtual void* SetColorI(uint8_t param_1, uint8_t param_2, uint8_t param_3, uint32_t param_4) { return nullptr; }
			virtual void* SetColorF(uint8_t param_1, uint8_t param_2, uint8_t param_3, uint32_t param_4) { return nullptr; }
			virtual void* SetColorRef(uint32_t param_1, uint32_t param_2) { return nullptr; }
			virtual void* SetColorRecursive(uint32_t param_1, uint32_t param_2, uint32_t param_3) { return nullptr; }
			virtual void* SetColorAndMakeChildlessF(uint32_t param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4) { return nullptr; }
			virtual void* SetOpacityFRecursive(uint32_t param_1, uint32_t param_2) { return nullptr; }
			virtual void* SetOpacityF(uint32_t param_1, uint32_t param_2) { return nullptr; }
			virtual void* SetOpacity(uint32_t param_1) { return nullptr; }
			virtual void* SetColorI(uint8_t param_1, uint32_t param_2) { return nullptr; }
			virtual void* GetCornerColor(uint32_t param_1, uint32_t param_2) { return nullptr; }
			virtual float GetCornerOpacityF(uint32_t param_1) { return 0.0f; }
			virtual void* GetSpriteInfo() { return nullptr; }
			virtual void* BindTexture() { return nullptr; }
			virtual void* SetSecondaryColorMultiplied(uint32_t param_1) { return nullptr; }
			virtual void* SetSecondaryColorMultipliedRecursive(uint32_t param_1) { return nullptr; }
		};

		static_assert(sizeof(CSprite) == 0x104);
	}
}