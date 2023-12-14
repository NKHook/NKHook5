#pragma once

#include "../Util/NewFramework.h"
#include "CReferenceCounted.h"

namespace NKHook5 {
	namespace Classes {
		class CFont : public CReferenceCounted {
		public:
			char pad_0004[16]; //0x0004
			nfw::string fontName; //0x0014
			char pad_002C[24]; //0x002C
		public:
			virtual ~CFont() {};
		};
	}
}