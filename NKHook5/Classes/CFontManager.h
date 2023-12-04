#pragma once

#include "Macro.h"
#include "IFontImporter.h"
#include "CFont.h"
#include <boost/shared_ptr.hpp>
#include <ghstl/string>

namespace NKHook5 {
	namespace Classes {
		using namespace Signatures;

		class CFontManager : public IFontImporter {
		public:
			boost::shared_ptr<CFont>* GetFont(boost::shared_ptr<CFont>* resultFont, ghstl::string* fontName) {
				return ThisCall<boost::shared_ptr<CFont>*, CFontManager*, boost::shared_ptr<CFont>*, ghstl::string*>(Sigs::CFontManager_GetFont, this, resultFont, fontName);
			};
		};
	}
}