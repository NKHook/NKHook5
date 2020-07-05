#pragma once
#include <string>

using namespace std;

enum class FlagType {
	Tower
};
class FlagHacker
{
public:
	FlagHacker();
	void addHackedFlag(FlagType* type, string* name, long flag);
};

