#pragma once

#include "Macro.h"
#include <ghstl/string>

#include "CUnzippedFile.h"

namespace NKHook5 {
	namespace Signatures {
		namespace CZipFile {
			static const char* SIG_CCTOR = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? 53 56 57 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B D9 ?? 5D ?? E8 ?? ?? ?? ?? ?? 45";
			static const char* SIG_OPEN = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 81 EC ?? ?? ?? ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F1 8B ?? ?? E8";
			static const char* SIG_LOADFROM = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 81 EC ?? ?? ?? ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B D9 8B ?? ?? 8B ?? ?? ?? 45";
		}
	}
	namespace Classes {
		class CZipFile {
			ghstl::string archivePath;
			char pad_0018[36]; //0x0018
			ghstl::string assetPath; //0x003C
			char pad_0054[40]; //0x0054
			ghstl::string* pStringIDK; //0x007C
		public:
			CZipFile() {
				ThisCall<CZipFile*, CZipFile*>(Signatures::CZipFile::SIG_CCTOR, this);
			}
			bool Open(ghstl::string* archivePath) {
				return ThisCall<bool, CZipFile*, ghstl::string*>(Signatures::CZipFile::SIG_OPEN, this, archivePath);
			}
			CUnzippedFile* LoadFrom(ghstl::string* assetPath, ghstl::string* param_2, ghstl::string* archivePassword) {
				return ThisCall<CUnzippedFile*, CZipFile*, ghstl::string*, ghstl::string*, ghstl::string*>(Signatures::CZipFile::SIG_LOADFROM, this, assetPath, param_2, archivePassword);
			}
			CUnzippedFile* LoadFrom(ghstl::string* assetPath, ghstl::string* param_2) {
				ghstl::string password("Q%_{6#Px]]");
				return ThisCall<CUnzippedFile*, CZipFile*, ghstl::string*, ghstl::string*, ghstl::string*>(Signatures::CZipFile::SIG_LOADFROM, this, assetPath, param_2, &password);
			}
		};
	}
}