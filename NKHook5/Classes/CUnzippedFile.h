#pragma once

#include "Macro.h"
#include <ghstl/string>

namespace NKHook5 {
	namespace Signatures {
		static const char* SIG_CCTOR = "56 8B F1 8D ?? ?? ?? 06 ?? ?? ?? ?? E8 ?? ?? ?? ?? ?? 46 ?? ?? ?? ?? ?? 8B";
	}
	namespace Classes {
		class CUnzippedFile {
		public:
			void* fileContent; //0x0004
			char pad_0008[16]; //0x0008
			int32_t fileSize; //0x0018
			ghstl::string filePath; //0x001C
			char pad_0034[4]; //0x0034
		public:
			CUnzippedFile() {
				ThisCall<CUnzippedFile*, CUnzippedFile*>(Signatures::SIG_CCTOR, this);
			}
			virtual ~CUnzippedFile() {};
		};
	}
}