#include "Draw.h"

#include "../../Classes/GLRenderLayer.h"
#include "../../MenuEditor/Editor.h"

#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_opengl3.h>

extern bool g_initedImgui;
namespace NKHook5
{
    namespace Patches
    {
        namespace GLRenderLayer
        {

            void RenderOpenGL() {
                ImGui_ImplWin32_NewFrame();
                ImGui_ImplOpenGL3_NewFrame();
                ImGui::NewFrame();

                MenuEditor::Editor::Render();

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }

            static uint64_t o_func;
            void __fastcall cb_hook(Classes::GLRenderLayer* pRenderer, uint32_t pad, uint32_t param_2) {
                return PLH::FnCast(o_func, &cb_hook)(pRenderer, pad, param_2);
                if (g_initedImgui) {
                    //RenderOpenGL();
                }
            }

            auto Draw::Apply() -> bool
            {
                const uintptr_t address = Utils::FindPattern("55 8B EC 6A ?? 68 ?? ?? ?? ?? 64 ?? ?? ?? ?? ?? 50 81 EC ?? ?? ?? ?? A1 34 ?? ?? ?? 33 C5 ?? 45 ?? 53 56 57 50 8D ?? ?? ?? A3 ?? ?? ?? ?? 8B F9 ?? 7D ?? C7 05");
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour(address, (const uintptr_t)&cb_hook, &o_func);
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
        }
    }
}