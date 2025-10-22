#include "C_GameSFXManager.h"

#include "../Signatures/Signature.h"
#include "Macro.h"

#include <Logging/Logger.h>

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace NKHook5;
using namespace NKHook5::Classes;
using namespace NKHook5::Signatures;

C_GameSFXManager* C_GameSFXManager::GetInstance() {
	auto instFn = reinterpret_cast<C_GameSFXManager*(__cdecl*)()>(GetAddressOf(Sigs::C_GameSFXManager_GetInstance));
	if (instFn == nullptr) {
		Print(LogLevel::ERR, "Failed to find C_GameSFXManager::GetInstance!");
		return nullptr;
	}
	return instFn();
}

void C_GameSFXManager::Play(int id) {
	return ThisCall<Sigs::C_GameSFXManager_Play, &C_GameSFXManager::Play>(this, id);
}