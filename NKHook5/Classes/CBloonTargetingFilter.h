#pragma once

namespace NKHook5
{
	namespace Classes
	{
		class CBloonTargetingFilter
		{
		public:
			char pad_0004[0x18]; //0x0004

			virtual ~CBloonTargetingFilter();
		}; //Size: 0x001C
		static_assert(sizeof(CBloonTargetingFilter) == 0x1C);
	}
}