#include "ParseTask.h"
#include "../../Signatures/Signature.h"

#include "../../Classes/CApplyStatusEffectTask.h"
#include "../../Classes/CWeaponFactory.h"
#include "../../Classes/CProjectile.h"
#include "../../Classes/CCollectableTask.h"
#include "../../Classes/Json.h"
#include "../../Classes/WeaponTaskHierarchy.h"

#include "../../ClassesEx/CProjectileExt.h"
#include "../../ClassesEx/CCollectableTaskExt.h"

#include <cstdint>

using namespace NKHook5;
using namespace NKHook5::Classes;
using namespace NKHook5::ClassesEx;
using namespace NKHook5::Patches;
using namespace NKHook5::Patches::CWeaponFactory;
using namespace NKHook5::Signatures;

static uint64_t o_func;
void ParseTask::cb_hook(const nfw::map<nfw::string, JsonValue>& jsonData, WeaponTaskHierarchy::SNode* parseResults, bool hasSubtasks, uint32_t param_4) noexcept
{
    //Call the original CWeaponFactory::ParseTask function
	auto ofn = std::bit_cast<decltype(&ParseTask::cb_hook)>(reinterpret_cast<void*>(o_func));
	(this->*ofn)(jsonData, parseResults, hasSubtasks, param_4);
    //Get the resulting task
    Classes::CWeaponTask* baseTask = parseResults->resultTask;

    //Find its type name
    std::string typeName = nfw::typeof(baseTask);

    //The typename is mangled, but it'll contain CProjectile. This is effectively if(self instanceof CProjectile) for you java devs
    if (typeName.find("CProjectile") != std::string::npos) {
        auto* projectileTask = reinterpret_cast<ClassesEx::CProjectileExt*>(baseTask);
        //Parse our custom json properties
        projectileTask->NO_CLEANUP = false;
        projectileTask->ALWAYS_UPDATE = false;
        if (!jsonData.empty()) {
			const auto& noCleanup = ReadPrimitive<bool>(jsonData, "NO_CLEANUP");
            if (noCleanup.has_value()) {
                projectileTask->NO_CLEANUP = noCleanup.value();
            }
			const auto& alwaysUpdate = ReadPrimitive<bool>(jsonData, "ALWAYS_UPDATE");
            if (alwaysUpdate.has_value()) {
                projectileTask->ALWAYS_UPDATE = alwaysUpdate.value();
            }
			const auto& noOgc = ReadPrimitive<bool>(jsonData, "NO_OGC");
            if (noOgc.has_value()) {
                projectileTask->NO_OGC = noOgc.value();
            }
        }
    }

    //Cool
    if (typeName.find("CCollectableTask") != std::string::npos) {
        auto* collectableExt = reinterpret_cast<ClassesEx::CCollectableTaskExt*>(baseTask);
        collectableExt->COLLECT_METHOD = ClassesEx::CollectMethod::DEFAULT;
        if (!jsonData.empty()) {
			const auto& collectMethod = ReadPrimitive<nfw::string>(jsonData, "COLLECT_METHOD");
            if (collectMethod.has_value()) {
                if (collectMethod.value() == "DEFAULT") {
                    collectableExt->COLLECT_METHOD = ClassesEx::CollectMethod::DEFAULT;
                }
                if (collectMethod.value() == "AUTOMATIC") {
                    collectableExt->COLLECT_METHOD = ClassesEx::CollectMethod::AUTOMATIC;
                }
            }
        }
    }
}

auto ParseTask::Apply() -> bool
{
    const void* address = Signatures::GetAddressOf(Sigs::CWeaponFactory_ParseTask);
    if (address)
    {
        auto* detour = new PLH::x86Detour((const uintptr_t)address, std::bit_cast<size_t>(&ParseTask::cb_hook), &o_func);
        if (detour->hook())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}
