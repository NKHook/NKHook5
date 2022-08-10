#pragma once

/*
* Extended CProjectile
* 
* Adds new fields and such to the base CProjectile class
*/

#include "../Classes/CProjectile.h"

namespace NKHook5 {
	namespace ClassesEx {
		class CProjectileExt : public Classes::CProjectile {
		public:
			bool NO_CLEANUP;
			bool ALWAYS_UPDATE;
		};
	}
}