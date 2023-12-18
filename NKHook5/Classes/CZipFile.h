#pragma once

#include "../../Util/NewFramework.h"
#include "Macro.h"

#include "CUnzippedFile.h"
#include "../../Signatures/Signature.h"

namespace NKHook5::Classes {
	using namespace Signatures;

	class CZipFile {
	public:
		overload_allocators
	public:
		nfw::string mArchivePath;
		char pad_0018[36]{}; //0x0018
		nfw::string mAssetPath; //0x003C
		char pad_0054[40]{}; //0x0054
		nfw::string* pStringIDK{}; //0x007C
		char pad_0080[20]{}; //0x0080
	public:
		CZipFile() {
			ThisConstruct<Sigs::CZipFile_CCTOR>(this);
		}
		bool Open(const nfw::string& archivePath, int param_2 = 0, int param_3 = 0) {
			return ThisCall<Sigs::CZipFile_Open, &CZipFile::Open>(this, archivePath, param_2, param_3);
		}
		CUnzippedFile* _LoadFrom(const nfw::string& assetPath, const nfw::string& param_2, const nfw::string& archivePassword) {
			return ThisCall<Sigs::CZipFile_LoadFrom, &CZipFile::_LoadFrom>(this, assetPath, param_2, archivePassword);
		}
		CUnzippedFile* LoadFrom(const nfw::string& assetPath, const nfw::string& param_2) {
			nfw::string password("Q%_{6#Px]]");
			return this->_LoadFrom(assetPath, param_2, password);
		}
	};
}