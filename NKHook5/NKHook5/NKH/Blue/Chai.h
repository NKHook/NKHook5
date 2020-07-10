#pragma once
#include <chaiscript/chaiscript.hpp>
class Chai
{
public:
	static void startChai();
	static void invokeKeyCallbacks(char key);
	static void invokeBloonEscapedCallbacks(class CBloonEscapedEvent& eventPtr);
	static void reloadScripts();
};