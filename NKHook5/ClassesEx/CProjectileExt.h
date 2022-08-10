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
			//Decides if the projectile can be cleaned by the OGC or not
			bool NO_CLEANUP;
			//Decides if the projectile can be paused by the OGC or not
			bool ALWAYS_UPDATE;
			//Decides wether the OGC should ignore the projectile or not
			bool NO_OGC;
		};
	}
}