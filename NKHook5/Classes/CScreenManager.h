#pragma once

#include "CBaseScreen.h"

namespace NKHook5 {
	namespace Classes {
		class CScreenManager : public CBaseScreen
		{
		public:
			char pad_00B0[24]; //0x00B0
		}; //Size: 0x00C8
	}
}