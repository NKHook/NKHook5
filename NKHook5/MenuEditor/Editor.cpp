#include "Editor.h"

#include <imgui.h>
#include "../Classes/CBloonsTD5Game.h"
#include "../Classes/CScreenManager.h"
#include <iostream>

using namespace NKHook5;
using namespace NKHook5::MenuEditor;

extern Classes::CBloonsTD5Game* g_appPtr;

void ScreenTree(Classes::CBaseScreen* screen) {
	if (ImGui::TreeNode(screen->screenName.c_str())) {
		for (Classes::CBaseScreen* childScreen : screen->children) {
			ScreenTree(childScreen);
		}
		ImGui::TreePop();
	}
}

void Editor::Render() {
	ImGui::Begin("UI Inspector");
	Classes::CScreenManager* screenManager = g_appPtr->basePointers.pCScreenManager;
	if (screenManager) {
		//printf("screenManager: %p", screenManager);
		//printf("pChildren: %p", &screenManager->children);
		//printf("screenManager has %d children", screenManager->children.count());
		//std::cin.get();
		for (Classes::CBaseScreen* childScreen : screenManager->children) {
			ScreenTree(childScreen);
			//printf("Child screen: %p", childScreen);
		}
		//std::cin.get();
	}
	ImGui::End();
}