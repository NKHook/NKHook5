#include "LoadCategory.h"

#include <ghstl/string>
#include "../../Classes/CTowerFactory.h"
#include "../../Extensions/Tower/TowerFlagsExt.h"
#include "../../Extensions/ExtensionManager.h"
#include "../../Signatures/Signature.h"

extern NKHook5::Classes::CTowerFactory* g_towerFactory;

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
                        std::vector<ghstl::string> towerTypes(stringCount + towerFlagExt->GetFlags().size());
                        printf("Copying old types...\n");
                        for (int i = 0; i < stringCount; i++) {
                            towerTypes[i] = stringList[i];
                            printf("Copied '%s'...\n", stringList[i].c_str());
                        }
                        printf("Old types copied!\n");
                        printf("Injecting new types...\n");
                        int idx = 0;
                        for (auto flagDef : towerFlagExt->GetFlags()) {
                            towerTypes[stringCount + idx] = flagDef;
                            idx++;
                            printf("Injected '%s'...\n", flagDef.c_str());
                        }
                        printf("New types injected!\n");
                        return PLH::FnCast(o_func, &cb_hook)(self, pad, category, towerTypes.data(), towerTypes.size(), indexMode);
                    }
                }

                return PLH::FnCast(o_func, &cb_hook)(self, pad, category, stringList, stringCount, indexMode);
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