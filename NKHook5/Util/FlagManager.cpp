#include "FlagManager.h"

using namespace NKHook5::Util;

FlagManager::FlagManager()
{
}

void FlagManager::Register(uint64_t numeric, const nfw::string& text)
{
	flags.emplace(numeric, text);
}

uint64_t FlagManager::Register(const nfw::string& text)
{
	uint64_t selectedId = 0;
	for (size_t i = 0; i < INT_MAX; i++) {
		if (IsIDAvailable(i)) {
			selectedId = i;
			break;
		}
	}
	if (selectedId == 0) {
		printf("Failed to register flag '%s', couldn't find an available ID!", text.c_str());
		return 0;
	}
	Register(selectedId, text);
	return selectedId;
}

bool FlagManager::IsIDAvailable(uint64_t id)
{
	if (id == 0) {
		return false;
	}
	for (const auto& flagData : flags) {
		if (flagData.first == id) {
			return false;
		}
	}
	return true;
}

bool FlagManager::IsVanilla(uint64_t id)
{
	for (int i = 0; i < 100; i++) {
		uint64_t numericId = static_cast<uint64_t>(1) << i;
		if (numericId == id)
		{
			return true;
		}
	}
	return false;
}

uint64_t FlagManager::GetFlag(const nfw::string& name)
{
	for (const auto& flagData : flags) {
		if (flagData.second == name) {
			return flagData.first;
		}
	}
	return 0;
}

nfw::string FlagManager::GetName(uint64_t flag)
{
	for (const auto& flagData : flags) {
		if (flagData.first == flag) {
			return flagData.second;
		}
	}
	return "INVALID";
}

const nfw::map<uint64_t, nfw::string>& FlagManager::GetAll()
{
	return this->flags;
}
