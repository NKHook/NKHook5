#pragma once

#include "../Utils.h"
#include "../Signatures/Signature.h"

template<typename T, typename... P>
T FastCall(NKHook5::Signatures::Sigs sig, P... params) {
	static void* sigFunc = NKHook5::Signatures::GetAddressOf(sig);
	return ((T(__fastcall*)(P...))sigFunc)(params...);
};

template<typename T, typename... P>
T ThisCall(NKHook5::Signatures::Sigs sig, P... params) {
	static void* sigFunc = NKHook5::Signatures::GetAddressOf(sig);
	return ((T(__thiscall*)(P...))sigFunc)(params...);
};

template<typename T, typename... P>
T CdeclCall(NKHook5::Signatures::Sigs sig, P... params) {
	static void* sigFunc = NKHook5::Signatures::GetAddressOf(sig);
	return ((T(__cdecl*)(P...))sigFunc)(params...);
};