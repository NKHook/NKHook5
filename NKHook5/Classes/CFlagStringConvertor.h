#pragma once

namespace NKHook5 {
	namespace Signatures {
		static const char* SIG_FLAGTOSTRING = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? 56 57 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? E8 ?? ?? ?? ?? 85";
	}
	namespace Classes {
		class CFlagStringConvertor
		{
		public:
			char pad_0000[4]; //0x0000
		}; //Size: 0x0004
	}
}