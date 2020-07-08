#pragma once
#include <string>

using namespace std;

class FlagHacker
{
public:
	FlagHacker();
	static void addHackedFlag(string* name, long flag);
};

