#include "pch.h"
#include "Chai.h"
#include "../Patches/FlagHacker.h"
#include <filesystem>
#include "../SDK/CBloonsTD5Game.h"
#include "../SDK/CGameSystemPointers.h"
#include "../SDK/WinInput.h"
#include "../../Utils.h"

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
CBloonsTD5Game& getGame() {
	return *Utils::getGame();
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

	chai->add(fun(&injectFlag), "injectFlag");
	chai->add(fun(&onKey), "onKey");
	chai->add(fun(&getGame), "getGame");

	utility::add_class<CBloonsTD5Game>(*m,
		"CBloonsTD5Game",
		{ 
		},
		{ 
			{fun(&CBloonsTD5Game::getWinInput), "getWinInput"}
		}
	);
	utility::add_class<WinInput>(*m,
		"WinInput",
		{
		},
		{
			{fun(&WinInput::getMousePos), "getMousePos"}
		}
	);
	utility::add_class<Vector2>(*m,
		"Vector2",
		{
		},
		{
			{fun(&Vector2::getX), "x"},
			{fun(&Vector2::getY), "y"}
		}
	);

	chai->add(m);

	string appdata = string(getenv("APPDATA"));
	string nkhookdir = appdata.append("/NKHook5");
	string pluginDir = nkhookdir.append("/Plugins");
	std::string ext(".chai");
	for (auto& p : fs::recursive_directory_iterator(pluginDir.c_str()))
	{
		if (p.path().extension() == ext) {
			new thread(runChaiFile, p.path().u8string());
		}
	}
}
