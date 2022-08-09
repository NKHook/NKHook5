#include "WeaponProjectileExt.h"

#include <Logging/Logger.h>

using namespace Common;
using namespace Common::Extensions;
using namespace Common::Extensions::Weapon;
using namespace Common::Logging;
using namespace Common::Logging::Logger;

WeaponProjectileExt::WeaponProjectileExt() : JsonExtension("WeaponProjectileExtras", "Assets/JSON/WeaponDefinitions/*/*.weapon")
{
}

void WeaponProjectileExt::UseJsonData(nlohmann::json content)
{
	if (content.is_null()) {
		Print(LogLevel::ERR, "%s was given a null document. The extension will do nothing!", this->GetName().c_str());
		return;
	}
	nlohmann::json tasks = content["tasks"];
	if (tasks.is_null()) {
		Print(LogLevel::ERR, "%s was given a weapon with null tasks?", this->GetName().c_str());
		return;
	}
	if (!tasks.is_array()) {
		Print(LogLevel::ERR, "%s was given a weapon with tasks that is not an array?", this->GetName().c_str());
		return;
	}
	for (nlohmann::json task : tasks) {
		if (!task.is_object()) {
			Print(LogLevel::ERR, "%s was given a list with non-object tasks", this->GetName().c_str());
			continue;
		}

	}
}
