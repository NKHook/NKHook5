#include "LoadCategory.h"

#include "../../Util/NewFramework.h"
#include <ghstl/string>

#include "../../Classes/CBloonFactory.h"
#include "../../Classes/CTowerFactory.h"
#include "../../Extensions/StatusEffect/StatusDefinitionsExt.h"
#include "../../Signatures/Signature.h"
#include "../../Util/FlagManager.h"

#include <Extensions/Tower/TowerFlagsExt.h>
#include <Extensions/StatusEffect/StatusFlagsExt.h>
#include <Extensions/ExtensionManager.h>

extern NKHook5::Classes::CTowerFactory* g_towerFactory;
NKHook5::Util::FlagManager g_towerFlags;
extern NKHook5::Classes::CBloonFactory* g_bloonFactory;
NKHook5::Util::FlagManager g_bloonStatusFlags;

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            using namespace Common;
            using namespace Common::Extensions;
            using namespace Common::Extensions::Generic;
            using namespace Common::Extensions::StatusEffect;
            using namespace Common::Extensions::Tower;
            using namespace NKHook5;
            using namespace NKHook5::Extensions;
            using namespace NKHook5::Extensions::StatusEffect;
            using namespace Signatures;

            static uint64_t o_func;
            void* __fastcall cb_hook(Classes::CFlagStringConvertor* self, uint32_t pad, int category, std::string* stringList, int stringCount, int indexMode) {
                //Hijack and load new tower ids
                if (self == g_towerFactory) {
                    if (category == 0) {
                        printf("Hijacking tower registration to inject new types...\n");
                        std::vector<std::string> allTowers;
                        auto* towerFlagExt = (TowerFlagExt*)ExtensionManager::GetByName("TowerFlags");
                        printf("Copying old types...\n");
                        for (int i = 0; i < stringCount; i++) {
                            uint64_t numericId = static_cast<uint64_t>(1) << i;
                            g_towerFlags.Register(numericId, stringList[i]);
                            allTowers.push_back(stringList[i]);
                            printf("Copied '%s' to slot '%llx'\n", stringList[i].c_str(), numericId);
                        }
                        printf("Old types copied!\n");
                        printf("Injecting new types...\n");
                        for (const std::string& flagDef : towerFlagExt->GetFlags()) {
                            uint64_t moddedSlot = g_towerFlags.Register(flagDef);
                            allTowers.push_back(flagDef);
                            printf("Injected '%s' at slot '%llx'\n", flagDef.c_str(), moddedSlot);
                        }
                        printf("New types injected!\n");
                        return ((void*(__thiscall*)(void*, int, void*, int, int))o_func)(self, category, allTowers.data(), allTowers.size(), indexMode);
                        //return PLH::FnCast(o_func, &cb_hook)(self, pad, category, towerTypes.data(), towerTypes.size(), indexMode);
                    }
                }

                //Hijack and load new status effect ids
                if (self == g_bloonFactory)
                {
                    //Status effect category
                    if (category == 1)
                    {
                        printf("Hijacking bloon status effect registration to inject new types...\n");
                        std::vector<std::string> allEffects;
                        auto* statusFlagExt = (Common::Extensions::StatusEffect::StatusFlagsExt*)ExtensionManager::GetByName("StatusFlags");
                        auto* statusDefsExt = (StatusDefinitionsExt*)ExtensionManager::GetByName("StatusDefinitions");
                        printf("Copying old types...\n");
                        for (int i = 0; i < stringCount; i++) {
                            uint64_t numericId = static_cast<uint64_t>(1) << i;
                            g_bloonStatusFlags.Register(numericId, stringList[i]);
                            allEffects.push_back(stringList[i]);
                            printf("Copied '%s' to slot '%llx'\n", stringList[i].c_str(), numericId);
                        }
                        printf("Old types copied!\n");
                        printf("Injecting new types...\n");
                        for (const std::string& flagDef : statusFlagExt->GetFlags()) {
                            uint64_t moddedSlot = g_bloonStatusFlags.Register(flagDef);
                            allEffects.push_back(flagDef);
                            printf("Injected '%s' at slot '%llx'\n", flagDef.c_str(), moddedSlot);
                        }
                        printf("New types injected!\n");

                        return ((void* (__thiscall*)(void*, int, void*, int, int))o_func)(self, category, allEffects.data(), allEffects.size(), indexMode);
                    }
                }

                return ((void* (__thiscall*)(void*, int, void*, int, int))o_func)(self, category, stringList, stringCount, indexMode);
            }

            auto LoadCategory::Apply() -> bool
            {
                const void* address = Signatures::GetAddressOf(Sigs::CFlagStringConvertor_LoadCategory);
                if(address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour((const uint64_t)address, (const uintptr_t)&cb_hook, &o_func);
                    if(detour->hook())
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
        }
    }
}