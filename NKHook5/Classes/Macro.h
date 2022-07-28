#pragma once

#include "../Utils.h"
#include "../../Signatures/Signature.h"

template<typename T, typename... P>
T FastCall(NKHook5::Signatures::Sigs sig, P... params) {
	static void* sigFunc = NKHook5::Signatures::GetAddressOf(sig);
	return ((T(__fastcall*)(P...))sigFunc)(params...);
};

template<typename T, typename... P>
T ThisCall(NKHook5::Signatures::Sigs sig, P... params) {
	static void* sigFunc = NKHook5::Signatures::GetAddressOf(sig);
	return ((T(__thiscall*)(P...))sigFunc)(params...);

	//if (sizeof...(params) == 0) {
	//	return FastCall<T, TyThis>(sig, self);
	//}
	////0 to pad EDX
	//return FastCall<T, TyThis, int, P...>(sig, self, 0, params...);
};