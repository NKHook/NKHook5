#pragma once

#include "CApp.h"

namespace NKHook5
{
	namespace Classes
	{
		class CBloonsTD5Game : public CApp
		{
		private:
			char pad_01C4[4]; //0x01C4
		public:
			virtual ~CBloonsTD5Game() {};
		};
	} // namespace Classes
	
} // namespace NKHook5
