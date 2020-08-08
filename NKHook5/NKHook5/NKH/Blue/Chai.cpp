#include "pch.h"
#include "Chai.h"
#include "../Patches/FlagHacker.h"
#include <filesystem>
#include "../SDK/CBloonsTD5Game.h"
#include "../SDK/CGameSystemPointers.h"
#include "../SDK/WinInput.h"
#include "../../Utils.h"
#include "../SDK/CTowerManager.h"
#include "../SDK/CBaseTower.h"
#include "../SDK/CCompoundSprite.h"
#include "../SDK/GameData.h"
#include "../SDK/CBloonEscapedEvent.h"
#include "../SDK/CBloon.h"
#include "../SDK/BloonData.h"

/*
Chai format funcs
*/
#pragma region Functions
void injectFlag(const string& name, int flag) {
	string* str = new string(name.c_str());
	FlagHacker::addHackedFlag(str, flag);
}
CBloonsTD5Game getGame() {
	return *Utils::getGame();
}
void cSleep(int millis) {
	Sleep(millis);
}
#pragma endregion

#pragma region Events
#pragma region onKey
typedef std::function<void(const char&)> onKeyCallback;
vector<onKeyCallback> onKeyCallbacks;
void onKey(const onKeyCallback& keyFunc)
{
	onKeyCallbacks.push_back(keyFunc);
}
void Chai::invokeKeyCallbacks(char key)
{
	for (int i = 0; i < onKeyCallbacks.size(); i++) {
		const onKeyCallback leCallback = onKeyCallbacks[i];
		leCallback(key);
	}
}
#pragma endregion
#pragma region onBloonEscaped
typedef std::function<void(CBloonEscapedEvent&)> onBloonEscapedCallback;
vector<onBloonEscapedCallback> onBloonEscapedCallbacks;
void onBloonEscaped(const onBloonEscapedCallback& theFunc)
{
	onBloonEscapedCallbacks.push_back(theFunc);
}
void Chai::invokeBloonEscapedCallbacks(CBloonEscapedEvent& eventPtr)
{
	for (int i = 0; i < onBloonEscapedCallbacks.size(); i++) {
		const onBloonEscapedCallback leCallback = onBloonEscapedCallbacks[i];
		leCallback(eventPtr);
	}
}
#pragma endregion
#pragma region onTowerUpgrade
typedef std::function<void(CTowerManager&, CBaseTower&, const int&)> onTowerUpgradeCallback;
vector<onTowerUpgradeCallback> onTowerUpgradeCallbacks;
void onTowerUpgrade(const onTowerUpgradeCallback& theFunc)
{
	onTowerUpgradeCallbacks.push_back(theFunc);
}
void Chai::invokeTowerUpgradedCallbacks(CTowerManager& towerManager, CBaseTower& tower, int upgradePath)
{
	/*cout << hex << &towerManager << endl;
	cout << hex << &tower << endl;
	cout << hex << upgradePath << endl;*/
	for (int i = 0; i < onTowerUpgradeCallbacks.size(); i++) {
		const onTowerUpgradeCallback leCallback = onTowerUpgradeCallbacks[i];
		leCallback(towerManager, tower, upgradePath);
	}
}
#pragma endregion
#pragma region onGameDataInitialized
typedef std::function<void()> onGameDataInitializedCallback;
vector<onGameDataInitializedCallback> onGameDataInitializedCallbacks;
void onGameDataInitialized(const onGameDataInitializedCallback& theFunc)
{
	onGameDataInitializedCallbacks.push_back(theFunc);
}
void Chai::invokeGameDataInitializedCallbacks()
{
	for (int i = 0; i < onGameDataInitializedCallbacks.size(); i++) {
		const onGameDataInitializedCallback leCallback = onGameDataInitializedCallbacks[i];
		leCallback();
	}
}
#pragma endregion
#pragma region onConsoleInput
typedef std::function<bool(string&)> onConsoleInputCallback;
vector<onConsoleInputCallback> onConsoleInputCallbacks;
void onConsoleInput(const onConsoleInputCallback& theFunc)
{
	onConsoleInputCallbacks.push_back(theFunc);
}
bool Chai::invokeConsoleInputCallbacks(string& input)
{
	bool called = false;
	for (int i = 0; i < onConsoleInputCallbacks.size(); i++) {
		const onConsoleInputCallback leCallback = onConsoleInputCallbacks[i];
		if (leCallback(input)) {
			called = true;
		}
	}
	return called;
}
#pragma endregion
#pragma endregion



/*
Setup
*/
vector<thread*> chaiThreads;

//If you complain ill have a problem
using namespace chaiscript;
namespace fs = std::filesystem;

//Chaiscript object
ChaiScript* chai;

void runChaiFile(string path) {
	try {
		chai->eval_file(path);
	}
	catch (std::exception ex) {
		cout << "An error occoured in file " << path << endl;
		cout << ex.what() << endl;
	}
}
void runAllChaiFiles() {
	string appdata = string(getenv("APPDATA"));
	string nkhookdir = appdata.append("/NKHook5");
	string pluginDir = nkhookdir.append("/Plugins");
	string ext(".chai");
	for (auto& p : fs::recursive_directory_iterator(pluginDir.c_str()))
	{
		if (p.path().extension() == ext) {
			chaiThreads.push_back(new thread(runChaiFile, p.path().u8string()));
		}
	}
}
void Chai::reloadScripts()
{
	cout << "Removing event hooks..." << endl;
	onKeyCallbacks.clear();
	onBloonEscapedCallbacks.clear();
	onTowerUpgradeCallbacks.clear();
	onConsoleInputCallbacks.clear();
	cout << "Removed event hooks" << endl;
	cout << "Killing chai threads..." << endl;
	for (int i = 0; i < chaiThreads.size(); i++) {
		TerminateThread(chaiThreads[i]->native_handle(), 0);
	}
	chaiThreads.clear();
	cout << "Killed chai threads" << endl;
	cout << "Clearing chai from memory" << endl;
	delete chai;
	cout << "Starting scripts..." << endl;
	startChai();
}


void Chai::startChai()
{
	//Initialize chai
	chai = new ChaiScript();

	//Create the module
	ModulePtr m = ModulePtr(new chaiscript::Module());

#pragma region ChaiInitFuncs
	chai->add(fun(&cSleep), "Sleep");
	chai->add(fun(&injectFlag), "injectFlag");
	chai->add(fun(&getGame), "getGame");
#pragma endregion
#pragma region ChaiInitEvents
	chai->add(fun(&onKey), "onKey");
	chai->add(fun(&onBloonEscaped), "onBloonEscaped");
	chai->add(fun(&onTowerUpgrade), "onTowerUpgrade");
	chai->add(fun(&onGameDataInitialized), "onGameDataInit");
	chai->add(fun(&onConsoleInput), "onConsoleInput");
#pragma endregion
#pragma region ChaiInitClasses
#pragma region CBloonsTD5Game
	utility::add_class<CBloonsTD5Game>(*m,
		"CBloonsTD5Game",
		{
		},
		{
			{fun(&CBloonsTD5Game::getWinInput), "getWinInput"},
			{fun(&CBloonsTD5Game::getCGameSystemPointers), "getCGameSystemPointers"}
		}
	);
#pragma endregion
#pragma region WinInput
	utility::add_class<WinInput>(*m,
		"WinInput",
		{
		},
		{
			{fun(&WinInput::getClickState), "getClickState"},
			{fun(&WinInput::getClickStartPos), "getClickStartPos"},
			{fun(&WinInput::getClickedMousePos), "getClickedMousePos"},
			{fun(&WinInput::getMousePos), "getMousePos"}
		}
	);
#pragma endregion
#pragma region CGameSystemPointers
	utility::add_class<CGameSystemPointers>(*m,
		"CGameSystemPointers",
		{
		},
		{
			{fun(&CGameSystemPointers::getCTowerManager), "getCTowerManager"},
			{fun(&CGameSystemPointers::getGameData), "getGameData"}
		}
	);
#pragma endregion
#pragma region CTowerManager
	utility::add_class<CTowerManager>(*m,
		"CTowerManager",
		{
		},
		{
			{fun(&CTowerManager::getTower), "getTower"},
			{fun(&CTowerManager::getLastTower), "getLastTower"},
			{fun(&CTowerManager::getTowerCount), "getTowerCount"},
			{fun(&CTowerManager::forEachTower), "forEachTower"}
		}
	);
#pragma endregion
#pragma region CBaseTower
	utility::add_class<CBaseTower>(*m,
		"CBaseTower",
		{
		},
		{
			{fun(&CBaseTower::getPosition), "getPosition"},
			{fun(&CBaseTower::getTypeFlag), "getTypeFlag"},
			{fun(&CBaseTower::setTypeFlag), "setTypeFlag"},
			{fun(&CBaseTower::isSelected), "isSelected"},
			{fun(&CBaseTower::getCCompoundSprite), "getCCompoundSprite"},
			{fun(&CBaseTower::isHovered), "isHovered"},
			{fun(&CBaseTower::incrementUpgradeLevel), "incrementUpgradeLevel"}
		}
	);
#pragma endregion
#pragma region Vector2
	utility::add_class<Vector2>(*m,
		"Vector2",
		{
		},
		{
			{fun(&Vector2::x), "X"},
			{fun(&Vector2::y), "Y"},
			{fun(&Vector2::getX), "getX"},
			{fun(&Vector2::getY), "getY"},
			{fun(&Vector2::setX), "setX"},
			{fun(&Vector2::setY), "setY"}
		}
	);
#pragma endregion
#pragma region GameData
	utility::add_class<GameData>(*m,
		"GameData",
		{
		},
		{
			{fun(&GameData::getCash), "getCash"},
			{fun(&GameData::getHealth), "getHealth"},
			{fun(&GameData::getCurrentMap), "getCurrentMap"},
			{fun(&GameData::setCash), "setCash"},
			{fun(&GameData::setHealth), "setHealth"}
		}
	);
#pragma endregion
#pragma region CBloonEscapedEvent
	utility::add_class<CBloonEscapedEvent>(*m,
		"CBloonEscapedEvent",
		{
		},
		{
			{fun(&CBloonEscapedEvent::getEscapedBloon), "getEscapedBloon"}
		}
	);
#pragma endregion
#pragma region CBloon
	utility::add_class<CBloon>(*m,
		"CBloon",
		{
		},
		{
			{fun(&CBloon::getSpriteSize), "getSpriteSize"},
			{fun(&CBloon::getBloonData), "getBloonData"}
		}
	);
#pragma endregion
#pragma region BloonData
	utility::add_class<BloonData>(*m,
		"BloonData",
		{
		},
		{
			{fun(&BloonData::getChildBloonFileName), "getChildBloonFileName"},
			{fun(&BloonData::getTypeName), "getTypeName"},
			{fun(&BloonData::getType), "getType"},
			{fun(&BloonData::getDamage), "getDamage"}
		}
	);
#pragma endregion
#pragma endregion

	//Add module with classes and shit
	chai->add(m);

	//Start all of the chai files
	runAllChaiFiles();
}
