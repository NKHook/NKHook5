#include "Editor.h"

#include <imgui.h>
#include "../Classes/CBloonsBaseScreen.h"
#include "../Classes/CBloonsTD5Game.h"
#include "../Classes/CScreenManager.h"
#include <iostream>

using namespace NKHook5;
using namespace NKHook5::MenuEditor;

extern Classes::CBloonsTD5Game* g_appPtr;

void ElementEditor(Classes::CBasePositionableObject* object) {
	ImGui::PushID(object);
	if (ImGui::TreeNode("Object")) {
		ImGui::InputFloat("X", &object->location.x, 1, 10);
		ImGui::InputFloat("Y", &object->location.y, 1, 10);
		ImGui::InputFloat("Z", &object->location.z, 1, 10);
		ImGui::TreePop();
	}
	ImGui::PopID();
}

void ScreenTree(Classes::CBaseScreen* screen) {
	if (ImGui::TreeNode(screen->screenName.c_str())) {
		for (Classes::CBaseScreen* childScreen : screen->children) {
			ScreenTree(childScreen);
		}
		Classes::CBloonsBaseScreen* bScreen = (Classes::CBloonsBaseScreen*)screen;
		for (Classes::CBasePositionableObject* object : bScreen->elements) {
			ElementEditor(object);
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