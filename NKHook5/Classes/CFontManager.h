#pragma once

#include "CFont.h"
#include "boost/shared_ptr"
#include <ghstl/string>

namespace NKHook5 {
	namespace Classes {
		class CFontManager {
		public:
			boost::shared_ptr<CFont>* GetFont(boost::shared_ptr<CFont>* resultFont, ghstl::string* fontName) {};
		};
	}
}