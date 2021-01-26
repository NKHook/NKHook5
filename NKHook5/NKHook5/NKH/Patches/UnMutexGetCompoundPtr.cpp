#include "pch.h"
#include "UnMutexGetCompoundPtr.h"
#include "../../Utils.h"

using namespace std;
UnMutexGetCompoundPtr::UnMutexGetCompoundPtr()
{
	int GetCompoundPtr = (int)Utils::findPattern(Utils::getModuleBase() + 0x518000, Utils::getBaseModuleEnd(), "55 8B EC 6A FF 68 ?? ?? ?? ?? 64 A1 00 00 00 00 50 83 EC 08 53 56 57 A1 ?? ?? ?? ?? 33 C5 50 8D 45 F4 64 A3 00 00 00 00 8B F1 8D 86 AC 00 00 00");
	int threadSafety = GetCompoundPtr + 0x37;
	Utils::UnprotectMem((void*)threadSafety, 8);
	memset((void*)threadSafety, 0x90, 8);
	cout << "Removed GetCompoundPtr mutex" << endl;
}
