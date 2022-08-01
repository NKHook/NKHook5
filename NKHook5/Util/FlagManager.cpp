#include "FlagManager.h"

using namespace NKHook5::Util;

FlagManager::FlagManager()
{
}

void FlagManager::Register(uint64_t numeric, std::string text)
{
	flags.emplace_back(numeric, text);
}

uint64_t FlagManager::Register(std::string text)
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
	for (auto flagData : flags) {
		if (flagData.first == id) {
			return false;
		}
	}
	return true;
}

uint64_t FlagManager::GetFlag(std::string name)
{
	for (auto flagData : flags) {
		if (flagData.second == name) {
			return flagData.first;
		}
	}
	return 0;
}

std::string FlagManager::GetName(uint64_t flag)
{
	for (auto flagData : flags) {
		if (flagData.first == flag) {
			return flagData.second;
		}
	}
	return "INVALID";
}

const std::vector<std::pair<uint64_t, std::string>>& FlagManager::GetAll()
{
	return this->flags;
}
