#pragma once

#include "Macro.h"
#include <ghstl/string>
#include "../../Signatures/Signature.h"

namespace NKHook5 {
	namespace Classes {
		using namespace Signatures;

		class CUnzippedFile {
		public:
			void* fileContent; //0x0004
			char pad_0008[16]; //0x0008
			int32_t fileSize; //0x0018
			ghstl::string filePath; //0x001C
			char pad_0034[4]; //0x0034
		public:
			CUnzippedFile() {
				ThisCall<CUnzippedFile*, CUnzippedFile*>(Sigs::CUnzippedFile_CCTOR, this);
			}
			virtual ~CUnzippedFile() {};
		};
	}
}