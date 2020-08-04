#pragma once
#include <chaiscript/chaiscript.hpp>
#include <string>

using namespace std;
class Chai
{
public:
	static void startChai();
	static void invokeKeyCallbacks(char key);
	static void invokeBloonEscapedCallbacks(class CBloonEscapedEvent& eventPtr);
	static void invokeTowerUpgradedCallbacks(class CTowerManager& towerManager, class CBaseTower& tower, int upgradePath);
	static void invokeGameDataInitializedCallbacks();
	static bool invokeConsoleInputCallbacks(string& input);
	static void reloadScripts();
};