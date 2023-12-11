#pragma once

#include "../IPatch.h"

#include "../../Classes/WeaponTaskHierarchy.h"
#include "../../Classes/Json.h"

namespace NKHook5::Patches::CWeaponFactory {
	using namespace NKHook5;
	using namespace NKHook5::Classes;

	class ParseTask : public IPatch {
		void cb_hook(const nfw::map<nfw::string, JsonValue>& jsonData, WeaponTaskHierarchy::SNode* parseResults, bool hasSubtasks, uint32_t param_4) noexcept;
	public:
		ParseTask() : IPatch("CWeaponFactory::ParseTask") {};
		auto Apply() -> bool override;
	};
}

