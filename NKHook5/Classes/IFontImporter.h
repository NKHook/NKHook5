#pragma once

namespace NKHook5 {
	namespace Classes {
		class IFontImporter
		{
		public:
			char pad_0000[20]; //0x0000
			void** pFontMap; //0x0014
			char pad_0018[24]; //0x0018
		}; //Size: 0x0030
	}
}