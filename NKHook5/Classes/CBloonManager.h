#pragma once

#include "CBloon.h"
#include "ObjectManager.h"

namespace NKHook5 {
	namespace Classes {
		class CBloonManager : public ObjectManager<CBloon*> {
		public:
			char targetingFilterStuff[6260]; //0x0014
		public:
		};
	}
}