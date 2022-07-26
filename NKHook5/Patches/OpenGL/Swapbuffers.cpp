#include "Swapbuffers.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_opengl3_loader.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

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

            void RenderOpenGL(HDC hdc, HWND hWnd) {
                ImGui_ImplWin32_NewFrame();
                ImGui_ImplOpenGL3_NewFrame();
                ImGui::NewFrame();

                ImGui::Begin("Test");
                ImGui::End();

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            }

            static bool inited = false;
            static uint64_t o_func;
            bool __stdcall hkSwapbuffers(HDC hdc, int b) {
                HWND hWnd = WindowFromDC(hdc);

                if (!inited && hWnd) {
                    SetupOpenGL(hWnd);
                    inited = true;
                }
                if (inited) {
                    RenderOpenGL(hdc, hWnd);
                }

                return PLH::FnCast(o_func, &hkSwapbuffers)(hdc, b);
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