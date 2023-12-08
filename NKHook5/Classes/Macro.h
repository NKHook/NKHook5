#pragma once

#include "../Signatures/Signature.h"

//Utils to extract type information
template<typename... Args>
struct pack { };
template<typename class_t = std::false_type>
struct extract_type
{
	typedef class_t type;
};
template<typename return_t, typename class_t, typename... args_t>
struct extract_type<return_t(class_t::*)(args_t...)>
{
	typedef class_t type;
	typedef return_t ret;
	typedef pack<args_t...> args;
};

template<NKHook5::Signatures::Sigs sig, typename ret_t, typename... args_t>
ret_t FastCall(args_t... params) {
	static void* sigFunc = NKHook5::Signatures::GetAddressOf(sig);
	return ((ret_t(__fastcall*)(args_t...))sigFunc)(params...);
};

template<NKHook5::Signatures::Sigs sig, typename func_t, typename class_t = extract_type<func_t>::class_t, typename ret_t = extract_type<func_t>::ret, typename... args_t>
ret_t ThisCall(func_t fn, class_t* self, args_t... args) {
	auto addr = NKHook5::Signatures::GetAddressOf(sig);
	static auto func = *reinterpret_cast<func_t*>(&addr);
	return (self->*func)(args...);
};

template<NKHook5::Signatures::Sigs sig, typename class_t, typename... args_t>
void ThisConstruct(class_t* self, args_t... args) {
	using func_t = void(__thiscall*)(class_t*, args_t...);
	auto addr = NKHook5::Signatures::GetAddressOf(sig);
	static auto func = *reinterpret_cast<func_t*>(&addr);
	return func(self, args...);
}

template<NKHook5::Signatures::Sigs sig, typename ret_t, typename... args_t>
ret_t CdeclCall(args_t... params) {
	static void* sigFunc = NKHook5::Signatures::GetAddressOf(sig);
	return ((ret_t(__cdecl*)(args_t...))sigFunc)(params...);
};