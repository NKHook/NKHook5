#pragma once

#include "../JsonExtension.h"

namespace Common {
	namespace Extensions {
		namespace Weapon {
			class WeaponProjectileExt : public JsonExtension {
			public:
				WeaponProjectileExt();
				virtual void UseJsonData(nlohmann::json content);
			};
		}
	}
}