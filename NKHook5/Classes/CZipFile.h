#pragma once

#include "Macro.h"
#include <ghstl/string>

#include "CUnzippedFile.h"
#include "../../Signatures/Signature.h"

namespace NKHook5 {
	namespace Classes {
		class CZipFile {
			ghstl::string archivePath;
			char pad_0018[36]; //0x0018
			ghstl::string assetPath; //0x003C
			char pad_0054[40]; //0x0054
			ghstl::string* pStringIDK; //0x007C
			char pad_0080[20]; //0x0080
		public:
			CZipFile() {
				ThisCall<CZipFile*, CZipFile*>(Signatures::Sigs::CZipFile_CCTOR, this);
			}
			bool Open(ghstl::string& archivePath) {
				return ThisCall<bool, CZipFile*, ghstl::string&, int, int>(Signatures::Sigs::CZipFile_Open, this, archivePath, 0, 0);
			}
			CUnzippedFile* LoadFrom(ghstl::string& assetPath, ghstl::string& param_2, ghstl::string& archivePassword) {
				return ThisCall<CUnzippedFile*, CZipFile*, ghstl::string&, ghstl::string&, ghstl::string&>(Signatures::Sigs::CZipFile_LoadFrom, this, assetPath, param_2, archivePassword);
			}
			CUnzippedFile* LoadFrom(ghstl::string& assetPath, ghstl::string& param_2) {
				ghstl::string password("Q%_{6#Px]]");
				return ThisCall<CUnzippedFile*, CZipFile*, ghstl::string&, ghstl::string&, ghstl::string&>(Signatures::Sigs::CZipFile_LoadFrom, this, assetPath, param_2, password);
			}
		};
	}
}