#pragma once

#include "../Utils.h"

template<typename T, typename... P>
T FastCall(const char* sig, P... params) {
	static uint32_t sigFunc = NKHook5::Utils::FindPattern(sig);
	return ((T(_fastcall*)(P...))sigFunc)(params...);
};

template<typename T, typename TyThis, typename... P>
T ThisCall(const char* sig, TyThis self, P... params) {
	//0 to pad EDX
	return FastCall<T, TyThis, int, P...>(sig, self, 0, params...);
};