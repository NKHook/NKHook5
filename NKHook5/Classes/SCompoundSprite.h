#pragma once

namespace NKHook5
{
	namespace Classes
	{
		struct SCompoundSprite
		{
		public:
			char pad_0000[88]; //0x0000
		}; //Size: 0x0058
		static_assert(sizeof(SCompoundSprite) == 0x58);
	}
}