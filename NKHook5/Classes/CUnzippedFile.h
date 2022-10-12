#pragma once

#include "../../Assets/Asset.h"
#include "../../Util/NewFramework.h"
#include "../../Signatures/Signature.h"
#include "Macro.h"
#include <ghstl/string>

namespace NKHook5 {
	namespace Classes {
		using namespace NKHook5;
		using namespace NKHook5::Signatures;
		using namespace NKHook5::Assets;

		struct FileReadResult {
			size_t content;
			uint8_t field1_0x4;
			uint8_t field2_0x5;
			uint8_t field3_0x6;
			uint8_t field4_0x7;
			size_t bytesRead;
			size_t readEnd;
		};

		class CUnzippedFile {
		public:
			overload_new
		public:
			void* fileContent;
			FileReadResult readResult;
			uint32_t fileSize;
			ghstl::string filePath;
			uint8_t field5_0x34;
			uint8_t field6_0x35;
			uint8_t field7_0x36;
			uint8_t field8_0x37;
		public:
			CUnzippedFile() {
				ThisCall<CUnzippedFile*, CUnzippedFile*>(Sigs::CUnzippedFile_CCTOR, this);
			}
			CUnzippedFile(std::shared_ptr<Asset> asset) {
				ThisCall<CUnzippedFile*, CUnzippedFile*>(Sigs::CUnzippedFile_CCTOR, this);

				this->filePath.assign(asset->GetFullPath().string());
				this->fileSize = asset->GetData().size();
				this->fileContent = malloc(this->fileSize);
				memcpy_s(this->fileContent, this->fileSize, asset->GetData().data(), this->fileSize);
			}
			virtual ~CUnzippedFile() {};
		};

		static_assert(sizeof(CUnzippedFile) == 0x38);
		static_assert(offsetof(CUnzippedFile, fileContent) == 0x4);
		static_assert(offsetof(CUnzippedFile, fileSize) == 0x18);
		static_assert(offsetof(CUnzippedFile, filePath) == 0x1C);
	}
}