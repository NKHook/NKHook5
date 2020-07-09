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

/*
Chai format funcs
*/
void injectFlag(const string& name, int flag) {
	string* str = new string(name.c_str());
	FlagHacker::addHackedFlag(str, flag);
}
typedef std::function<void(const char&)> onKeyCallback;
vector<onKeyCallback> onKeyCallbacks;
void onKey(const onKeyCallback& keyFunc)
{
	onKeyCallbacks.push_back(keyFunc);
}
void Chai::invokeKeyCallbacks(char key) {
	for (int i = 0; i < onKeyCallbacks.size(); i++) {
		const onKeyCallback leCallback = onKeyCallbacks[i];
		leCallback(key);
	}
}
CBloonsTD5Game getGame() {
	return *Utils::getGame();
}
void cSleep(int millis) {
	Sleep(millis);
}



/*
Setup
*/
using namespace chaiscript;
namespace fs = std::filesystem;

ChaiScript* chai;

void runChaiFile(string path) {
	chai->eval_file(path);
}

void Chai::startChai()
{
	chai = new ChaiScript();

	chaiscript::ModulePtr m = chaiscript::ModulePtr(new chaiscript::Module());

	chai->add(fun(&cSleep), "Sleep");
	chai->add(fun(&injectFlag), "injectFlag");
	chai->add(fun(&onKey), "onKey");
	chai->add(fun(&getGame), "getGame");

	utility::add_class<CBloonsTD5Game>(*m,
		"CBloonsTD5Game",
		{ 
		},
		{ 
			{fun(&CBloonsTD5Game::getWinInput), "getWinInput"},
			{fun(&CBloonsTD5Game::getCGameSystemPointers), "getCGameSystemPointers"}
		}
	);
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
	utility::add_class<CGameSystemPointers>(*m,
		"CGameSystemPointers",
		{
		},
		{
			{fun(&CGameSystemPointers::getCTowerManager), "getCTowerManager"}
		}
	);
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
	utility::add_class<CBaseTower>(*m,
		"CBaseTower",
		{
		},
		{
			{fun(&CBaseTower::getPosition), "getPosition"},
			{fun(&CBaseTower::getTypeFlag), "getTypeFlag"},
			{fun(&CBaseTower::isSelected), "isSelected"},
			{fun(&CBaseTower::getCCompoundSprite), "getCCompoundSprite"},
			{fun(&CBaseTower::isHovered), "isHovered"}
		}
	);
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

	chai->add(m);

	string appdata = string(getenv("APPDATA"));
	string nkhookdir = appdata.append("/NKHook5");
	string pluginDir = nkhookdir.append("/Plugins");
	string ext(".chai");
	for (auto& p : fs::recursive_directory_iterator(pluginDir.c_str()))
	{
		if (p.path().extension() == ext) {
			try {
				new thread(runChaiFile, p.path().u8string());
			}
			catch (...) {
				cout << "An error occoured in " << p.path().filename() << endl;
			}
		}
	}
}
