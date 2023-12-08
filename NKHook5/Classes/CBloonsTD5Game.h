#pragma once

#include "CApp.h"

namespace NKHook5::Classes
{
	class CBloonsTD5Game : public CApp
	{
	private:
		char pad_01C4[4]; //0x01C4
	public:
		~CBloonsTD5Game() override = default;
	};
} // namespace NKHook5::Classes
	

