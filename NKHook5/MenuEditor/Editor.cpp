#include "Editor.h"

#include <imgui.h>

#include "../Classes/CBloonsBaseScreen.h"
#include "../Classes/CBloonsTD5Game.h"
#include "../Classes/CScreenManager.h"
#include "../Classes/CTowerManager.h"

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
	if(screen->mScreenName.empty())
		return;

	if (ImGui::TreeNode(screen->mScreenName.c_str())) {
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

	ImGui::Begin("NKHook5 Runtime Editor");
	if(ImGui::CollapsingHeader("Screens"))
	{
		auto* screenManager = g_appPtr->mScreenManager;
		if (screenManager) {
			for (Classes::CBaseScreen* childScreen : screenManager->children) {
				ScreenTree(childScreen);
			}
		}
	}
	if(ImGui::CollapsingHeader("Game Data"))
	{
		if(ImGui::CollapsingHeader("Towers"))
		{
			auto* towerMgr = g_appPtr->mGameSystemPointers->mTowerMgr;
			auto* towerFactory = g_appPtr->mGameSystemPointers->mTowerFactory;
			if(towerMgr != nullptr)
			{
				for(const auto& tower : towerMgr->objects)
				{
					auto addrStr = std::format("{:#010x}", reinterpret_cast<size_t>(tower));
					auto formatted = std::format("Tower @ {0}", addrStr);
					if(ImGui::CollapsingHeader(formatted.c_str()))
					{
						ImGui::InputText("Address", const_cast<char*>(addrStr.c_str()), addrStr.size(), ImGuiInputTextFlags_ReadOnly);
						ImGui::InputFloat("Position X", &tower->mLocation.x);
						ImGui::InputFloat("Position Y", &tower->mLocation.y);
						ImGui::InputInt("Reference Count", &tower->mRefCount, ImGuiInputTextFlags_ReadOnly);

						auto flagStr = std::format("{0} ({1})", tower->mTypeFlags, towerFactory->FlagToString(0, tower->mTypeFlags));
						ImGui::InputText("Type Flags", const_cast<char*>(flagStr.c_str()), flagStr.size(), ImGuiInputTextFlags_ReadOnly);
					}
				}
			}
		}
		if(ImGui::CollapsingHeader("Bloons"))
		{

		}
	}
	ImGui::End();
}