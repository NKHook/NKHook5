#pragma once

#include "../Util/NewFramework.h"
#include "Macro.h"
#include "IFontImporter.h"
#include "CFont.h"

#include <boost/shared_ptr.hpp>

namespace NKHook5::Classes {
	using namespace Signatures;

	class CFontManager : public IFontImporter {
	public:
		boost::shared_ptr<CFont>* GetFont(boost::shared_ptr<CFont>* resultFont, const nfw::string& fontName) {
			return ThisCall<Sigs::CFontManager_GetFont, &CFontManager::GetFont>(this, resultFont, fontName);
		};
	};
}