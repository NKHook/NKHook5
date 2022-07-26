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
		char addrBuf[64];
		sprintf_s(addrBuf, 64, "%p", object);
		bool needsUpdate = ImGui::InputText("Address", addrBuf, 64);
		needsUpdate |= ImGui::SliderFloat("X", &object->location.x, -1000, 1000);
		needsUpdate |= ImGui::SliderFloat("Y", &object->location.y, -1000, 1000);
		needsUpdate |= ImGui::SliderFloat("Z", &object->location.z, -1000, 1000);
		if (needsUpdate) {
			object->SetXYZ(object->location);
		}
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
	ImGui::ShowDemoWindow();

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