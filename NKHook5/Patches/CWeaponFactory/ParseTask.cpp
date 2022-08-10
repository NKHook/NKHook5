#include "ParseTask.h"
#include "../../Signatures/Signature.h"
#include "../../Classes/CProjectile.h"
#include "../../Classes/CWeaponFactory.h"
#include "../../ClassesEx/CProjectileExt.h"
#include "../../Util/NewFramework.h"
#include <Logging/Logger.h>

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace NKHook5;
using namespace NKHook5::Patches;
using namespace NKHook5::Patches::CWeaponFactory;
using namespace NKHook5::Signatures;

struct parseResult_t {
    char pad_0000[16]; //0x0000
    ClassesEx::CProjectileExt* resultTask; //0x0010
};

static uint64_t o_func;
void* __fastcall cb_hook(Classes::CWeaponFactory* self, int pad, void* param_1, parseResult_t* parseResults, bool param_3, int param_4) {
    //Get the parsed json document handle
    Classes::JsonObject documentHandle = self->currentDocument;
    //Call the original CWeaponFactory::ParseTask function
    void* result = PLH::FnCast(o_func, &cb_hook)(self, pad, param_1, parseResults, param_3, param_4);
    //Get the resulting tasl
    ClassesEx::CProjectileExt* baseTask = parseResults->resultTask;

    //Find its type name
    std::string typeName = nfw::typeof(baseTask);

    //The typename is mangled, but it'll contain CProjectile. This is effectively if(self instanceof CProjectile) for you java devs
    if (typeName.find("CProjectile") != std::string::npos) {
        //Parse our custom json properties
        baseTask->NO_CLEANUP = false;
        baseTask->ALWAYS_UPDATE = false;
        if (documentHandle.dataMap != nullptr) {
            Classes::JsonPropertyValue* noCleanup = documentHandle.Get("NO_CLEANUP");
            if (noCleanup != nullptr) {
                baseTask->NO_CLEANUP = noCleanup->value.boolValue;
            }
            Classes::JsonPropertyValue* alwaysUpdate = documentHandle.Get("ALWAYS_UPDATE");
            if (alwaysUpdate != nullptr) {
                baseTask->ALWAYS_UPDATE = alwaysUpdate->value.boolValue;
            }
        }
    }
    return result;
}

auto ParseTask::Apply() -> bool
{
    const void* address = Signatures::GetAddressOf(Sigs::CWeaponFactory_ParseTask);
    if (address)
    {
        PLH::x86Detour* detour = new PLH::x86Detour((const uintptr_t)address, (const uintptr_t)&cb_hook, &o_func);
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
