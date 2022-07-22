#pragma once

#include "Macro.h"
#include "IFontImporter.h"
#include "CFont.h"
#include "boost/shared_ptr"
#include <ghstl/string>

namespace NKHook5 {
	namespace Signatures {
		namespace CFontManager {
			static const char* SIG_GETFONT = "55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 83 EC ?? 56 57 A1 34 ?? ?? ?? 33 C5 50 8D ?? ?? ?? A3 ?? ?? ?? ?? ?? 45 ?? ?? ?? ?? ?? 8D ?? ?? 8B";
		}
	}
	namespace Classes {
		class CFontManager : public IFontImporter {
		public:
			boost::shared_ptr<CFont>* GetFont(boost::shared_ptr<CFont>* resultFont, ghstl::string* fontName) {
				return ThisCall<boost::shared_ptr<CFont>*, CFontManager*, boost::shared_ptr<CFont>*, ghstl::string*>(Signatures::CFontManager::SIG_GETFONT, this, resultFont, fontName);
			};
		};
	}
}