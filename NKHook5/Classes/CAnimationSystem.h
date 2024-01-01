#pragma once

#include <cstdint>

namespace NKHook5::Classes
{
	class CAnimationSystem
	{
	public:
		char pad_0000[56]{}; //0x0000
		int32_t mPlayMode{}; //0x0038
		char pad_003C[12]{}; //0x003C
		class CCompoundSprite* mCompoundSprite = nullptr; //0x0048
		char pad_004C[36]{}; //0x004C
	}; //Size: 0x0070

	static_assert(sizeof(CAnimationSystem) == 0x70);
}