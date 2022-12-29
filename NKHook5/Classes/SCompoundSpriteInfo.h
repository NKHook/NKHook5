#pragma once

namespace NKHook5
{
	namespace Classes
	{
		struct SCompoundSpriteInfo
		{
		public:
			char pad_0000[88]; //0x0000
		}; //Size: 0x0058
		static_assert(sizeof(SCompoundSpriteInfo) == 0x58);
	}
}