#include "LoadCategory.h"

#include <ghstl/string>
#include "../../Classes/CTowerFactory.h"
#include "../../Extensions/Tower/TowerFlagsExt.h"
#include "../../Extensions/ExtensionManager.h"
#include "../../Signatures/Signature.h"

extern NKHook5::Classes::CTowerFactory* g_towerFactory;
std::vector<ghstl::string> g_vanillaTowerTypes;
std::vector<ghstl::string> g_allTowerTypes;
std::vector<ghstl::string> g_moddedTowerTypes;

namespace NKHook5
{
    namespace Patches
    {
        namespace CFlagStringConvertor
        {
            using namespace Signatures;

            static uint64_t o_func;
            void* __fastcall cb_hook(Classes::CFlagStringConvertor* self, uint32_t pad, int category, ghstl::string* stringList, int stringCount, int indexMode) {
                if ((void*)self == (void*)&g_towerFactory->flagStringConvertor) {
                    if (category == 0 || category == 5) {
                        printf("Hijacking tower registration to inject new types...\n");
                        auto* towerFlagExt = (Extensions::Tower::TowerFlagExt*)Extensions::ExtensionManager::GetByName("TowerFlags");
                        g_vanillaTowerTypes = std::vector<ghstl::string>(stringCount + 1);
                        g_allTowerTypes = std::vector<ghstl::string>(stringCount + towerFlagExt->GetFlags().size() + 1);
                        g_moddedTowerTypes = std::vector<ghstl::string>(towerFlagExt->GetFlags().size() + 1);
                        printf("Copying old types...\n");
                        for (int i = 0; i < stringCount; i++) {
                            g_vanillaTowerTypes[i] = stringList[i];
                            g_allTowerTypes[i] = stringList[i];
                            printf("Copied '%s'...\n", stringList[i].c_str());
                        }
                        printf("Old types copied!\n");
                        printf("Injecting new types...\n");
                        int idx = 0;
                        for (auto flagDef : towerFlagExt->GetFlags()) {
                            g_moddedTowerTypes[idx] = flagDef;
                            g_allTowerTypes[stringCount + idx] = flagDef;
                            idx++;
                            printf("Injected '%s'...\n", flagDef.c_str());
                        }
                        printf("New types injected!\n");
                        return ((void*(__thiscall*)(void*, int, void*, int, int))o_func)(self, category, g_allTowerTypes.data(), g_allTowerTypes.size(), indexMode);
                        //return PLH::FnCast(o_func, &cb_hook)(self, pad, category, towerTypes.data(), towerTypes.size(), indexMode);
                    }
                }

                return ((void* (__thiscall*)(void*, int, void*, int, int))o_func)(self, category, stringList, stringCount, indexMode);
                //return PLH::FnCast(o_func, &cb_hook)(self, pad, category, stringList, stringCount, indexMode);
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