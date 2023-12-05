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
		bool needsUpdate = ImGui::InputText("Address", addrBuf, 64, ImGuiInputTextFlags_ReadOnly);
		needsUpdate |= ImGui::SliderFloat("X", &object->mLocation.x, -1000, 1000);
		needsUpdate |= ImGui::SliderFloat("Y", &object->mLocation.y, -1000, 1000);
		needsUpdate |= ImGui::SliderFloat("Z", &object->mLocation.z, -1000, 1000);
		if (needsUpdate) {
			object->mDirty = false;
		}
		ImGui::TreePop();
	}
	ImGui::PopID();
}

void ScreenTree(Classes::CBaseScreen* screen) {
	if(screen->screenName.empty())
		return;

	if (ImGui::TreeNode(screen->screenName.c_str())) {
		//Display the screen's memory address
		char addrBuf[64];
		sprintf_s(addrBuf, 64, "%p", screen);
		ImGui::InputText("Address", addrBuf, 64, ImGuiInputTextFlags_ReadOnly);

		//Display the screen tree
		int maxIter = 15;
		for (Classes::CBaseScreen* childScreen : screen->children) {
			ScreenTree(childScreen);
			maxIter--;
			if (maxIter <= 0) {
				break;
			}
		}

		//Display the screen objects
		auto* bScreen = reinterpret_cast<Classes::CBloonsBaseScreen*>(screen);
		/*for (Classes::CBasePositionableObject* object : bScreen->) {
			ElementEditor(object);
		}*/
		ImGui::TreePop();
	}
}

void Editor::Render() {
	ImGui::ShowDemoWindow();

	ImGui::Begin("UI Inspector");
	Classes::CScreenManager* screenManager = g_appPtr->basePointers.pCScreenManager;
	if (screenManager) {
		for (Classes::CBaseScreen* childScreen : screenManager->children) {
			ScreenTree(childScreen);
		}
	}
	ImGui::End();
}