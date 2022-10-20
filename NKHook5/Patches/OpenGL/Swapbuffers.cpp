#include "Swapbuffers.h"

#include "../../MenuEditor/Editor.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_opengl3_loader.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern int32_t maxProjectilesTotal;
extern int32_t maxProjectileUpdates;
extern int32_t maxBloonUpdates;
extern int32_t bloonPassDenom;

bool g_initedImgui = false;
uint64_t currentFrame = 0;
namespace NKHook5
{
    namespace Patches
    {
        namespace OpenGL
        {
            WNDPROC gameWndProc;
            LRESULT APIENTRY hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
            {
                if (!gameWndProc) {
                    return 0;
                }
                ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
                if (ImGui::GetIO().WantCaptureMouse) {
                    return true;
                }
                return CallWindowProcA(gameWndProc, hWnd, uMsg, wParam, lParam);
            }

            void SetupOpenGL(HWND gameWindow) {
                ImGui::CreateContext();
                ImGuiIO& io = ImGui::GetIO();
                ImGui::StyleColorsDark();
                ImGui_ImplOpenGL3_Init();
                ImGui_ImplWin32_Init(gameWindow);
                gameWndProc = (WNDPROC)SetWindowLongPtrA(gameWindow, GWLP_WNDPROC, (LONG_PTR)hkWndProc);
            }
            
            void RenderOpenGL() {
                ImGui_ImplWin32_NewFrame();
                ImGui_ImplOpenGL3_NewFrame();
                ImGui::NewFrame();

                //MenuEditor::Editor::Render();

#ifdef _DEBUG
                ImGui::Begin("Update cap test");
                ImGui::InputInt("Projectile count cap", &maxProjectilesTotal, 1, 50);
                ImGui::InputInt("Projectile update cap", &maxProjectileUpdates, 1, 50);
                ImGui::InputInt("Bloon update cap", &maxBloonUpdates, 1, 50);
                ImGui::InputInt("Bloon update bypass denominator", &bloonPassDenom, 1, 50);
                ImGui::End();
                
                ImGui::ShowDemoWindow();
#endif

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }

            static uint64_t o_func;
            bool __stdcall hkSwapbuffers(HDC hdc) {
                HWND hWnd = WindowFromDC(hdc);

                if (!g_initedImgui && hWnd) {
                    SetupOpenGL(hWnd);
                    //SetWindowTextA(hWnd, "Bloons TD5 | NKHook5");
                    g_initedImgui = true;
                }
                if (g_initedImgui) {
                    RenderOpenGL();
                }
                currentFrame++;
                return PLH::FnCast(o_func, &hkSwapbuffers)(hdc);
            }

            auto Swapbuffers::Apply() -> bool
            {
                HMODULE hOpenGL = GetModuleHandleA("OPENGL32.dll");
                if (!hOpenGL) {
                    printf("OpenGL32.dll couldn't be found");
                    return false;
                }
                const uintptr_t address = (const uintptr_t)GetProcAddress(hOpenGL, "wglSwapBuffers");
                if (address)
                {
                    PLH::x86Detour* detour = new PLH::x86Detour(address, (const uintptr_t)&hkSwapbuffers, &o_func);
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