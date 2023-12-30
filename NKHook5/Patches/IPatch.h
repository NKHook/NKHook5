#pragma once

#include <string>
#include <polyhook2/Detour/x86Detour.hpp>
#include <polyhook2/ZydisDisassembler.hpp>

namespace NKHook5::Patches
{
	class IPatch
	{
		static inline PLH::ZydisDisassembler* dis = new PLH::ZydisDisassembler(PLH::Mode::x86);
		std::string name;
	public:
		IPatch(std::string name);
		auto GetName() -> std::string;
		auto GetDis() -> PLH::ZydisDisassembler&;
		void WriteBytes(uintptr_t address, const char* bytes, size_t len);
		virtual auto Apply() -> bool;
	};
} // namespace NKHook5::Patches