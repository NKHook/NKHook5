#include "Editor.h"

#include <imgui.h>

#include "../Classes/CBloonManager.h"
#include "../Classes/CBloonFactory.h"
#include "../Classes/CBloonsBaseScreen.h"
#include "../Classes/CBloonsTD5Game.h"
#include "../Classes/CScreenManager.h"
#include "../Classes/CTowerManager.h"

#include <iostream>

using namespace NKHook5;
using namespace NKHook5::MenuEditor;

extern Classes::CBloonsTD5Game* g_appPtr;

void ElementEditor(Classes::CBasePositionableObject* object)
{
	auto addrStr = std::format("{:#010x}", reinterpret_cast<size_t>(object));
	ImGui::InputText("Address", const_cast<char*>(addrStr.c_str()), addrStr.size(), ImGuiInputTextFlags_ReadOnly);
	ImGui::InputFloat("Position X", &object->mLocation.x);
	ImGui::InputFloat("Position Y", &object->mLocation.y);
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
	static bool show = false;

	if(ImGui::IsKeyPressed(ImGuiKey_RightShift, false))
		show = !show;

	if(!show)
		return;

	ImGui::Begin("NKHook5 Runtime Editor", &show);
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
		if(ImGui::TreeNode("Towers"))
		{
			auto* towerMgr = g_appPtr->mGameSystemPointers->mTowerMgr;
			auto* towerFactory = g_appPtr->mGameSystemPointers->mTowerFactory;
			if(towerMgr != nullptr)
			{
				for(const auto& tower : towerMgr->objects)
				{
					auto addrStr = std::format("{:#010x}", reinterpret_cast<size_t>(tower));
					auto formatted = std::format("Tower @ {0}", addrStr);
					if(ImGui::TreeNode(formatted.c_str()))
					{
						ElementEditor(tower);
						ImGui::InputInt("Reference Count", &tower->mRefCount, ImGuiInputTextFlags_ReadOnly);
						auto flagStr = std::format("{0} ({1})", tower->mTypeFlags, towerFactory->FlagToString(0, tower->mTypeFlags));
						ImGui::InputText("Type Flags", const_cast<char*>(flagStr.c_str()), flagStr.size(), ImGuiInputTextFlags_ReadOnly);
						ImGui::InputInt("Pop Count", &tower->mPopCount);
						ImGui::Checkbox("Selected", &tower->mSelected);
						ImGui::Checkbox("Sellable", &tower->mSellable);
						ImGui::Checkbox("Upgradable", &tower->mUpgradable);
						ImVec4 color = ImGui::ColorConvertU32ToFloat4(tower->mColor);
						ImGui::ColorPicker4("Color", &color.x);
						tower->mColor = ImGui::ColorConvertFloat4ToU32(color);
						ImGui::Checkbox("Firing", &tower->mFiring);
						ImGui::InputFloat("Lifetime", &tower->mLifetime);
						ImGui::InputFloat("Time Alive", &tower->mAliveTime);
						ImGui::Checkbox("Please Destroy", &tower->mPleaseDestroy);
						ImGui::InputInt("Left Upgrades", &tower->mLeftUpgrades);
						ImGui::InputInt("Right Upgrades", &tower->mRightUpgrades);
						ImGui::InputInt("Sell Price", &tower->mSellPrice);
						auto targetStr = std::format("{0} ({1})", tower->mTargetingFlags, towerFactory->FlagToString(1, tower->mTargetingFlags));
						ImGui::InputScalar(std::format("Target {0}", targetStr).c_str(), ImGuiDataType_U64, &tower->mTargetingFlags);
						ImGui::Checkbox("Hovered", &tower->mHovered);
						ImGui::TreePop();
					}
				}
			}
			ImGui::TreePop();
		}
		if(ImGui::TreeNode("Bloons"))
		{
			auto* bloonMgr = g_appPtr->mGameSystemPointers->mBloonMgr;
			auto* bloonFactory = g_appPtr->mGameSystemPointers->mBloonFactory;
			if(bloonMgr != nullptr)
			{
				for (const auto& bloon : bloonMgr->objects)
				{
					auto addrStr = std::format("{:#010x}", reinterpret_cast<size_t>(bloon));
					auto formatted = std::format("Bloon @ {0}", addrStr);
					if(ImGui::TreeNode(formatted.c_str()))
					{
						ElementEditor(bloon);
						if(ImGui::TreeNode("Definition"))
						{
							auto* definition = bloon->mBloonDefinition;
							if(ImGui::TreeNode("ChildBloons"))
							{
								for(const auto& child : definition->mChildBloons)
								{
									ImGui::Text("%s", child.c_str());
								}
								ImGui::TreePop();
							}
							ImGui::InputText("SpriteFile", const_cast<char*>(definition->mSpriteFile.c_str()), definition->mSpriteFile.size(), ImGuiInputTextFlags_ReadOnly);
							auto statusStr = std::format("{0} ({1})", definition->mStatusImmunity, bloonFactory->FlagToString(1, definition->mStatusImmunity));
							ImGui::InputScalar(std::format("Status Immunity {0}", statusStr).c_str(), ImGuiDataType_U32, &definition->mStatusImmunity);
							ImGui::InputInt("RBE", &definition->mRBE);
							ImGui::InputFloat("Radius", &definition->mRadius);
							ImGui::InputFloat("Speed Multiplier", &definition->mSpeedMultiplier);
							ImGui::Checkbox("Can Go Underground", &definition->mCanGoUnderground);
							ImGui::Checkbox("Rotate To Path Direction", &definition->mRotateToPathDirection);
							ImGui::InputFloat("Initial Health", &definition->mInitialHealth);
							ImGui::TreePop();
						}
						auto statusStr = std::format("{0} ({1})", bloon->mStatusImmunity, bloonFactory->FlagToString(1, bloon->mStatusImmunity));
						ImGui::InputScalar(std::format("Status Immunity {0}", statusStr).c_str(), ImGuiDataType_U32, &bloon->mStatusImmunity);
						auto drawLayerStr = std::format("{0} ({1})", bloon->mDrawLayer, bloonFactory->FlagToString(3, bloon->mDrawLayer));
						ImGui::InputScalar(std::format("Draw Layer {0}", drawLayerStr).c_str(), ImGuiDataType_U32, &bloon->mDrawLayer);
						ImGui::InputFloat("Health", &bloon->mHealth);
						ImGui::InputFloat("Progress", &bloon->mProgress);
						ImGui::InputFloat("Velocity X", &bloon->mVelocity.x);
						ImGui::InputFloat("Velocity Y", &bloon->mVelocity.y);
						ImGui::InputFloat("Position X", &bloon->mLocation.x);
						ImGui::InputFloat("Position Y", &bloon->mLocation.y);
						ImGui::InputFloat("Turn Timer", &bloon->mTurnTimer);
						ImGui::InputFloat("Last Progress", &bloon->mLastProgress);
						ImGui::TreePop();
					}
				}
			}
			ImGui::TreePop();
		}
	}
	ImGui::End();
}