#pragma once

#include <string>

namespace NKHook5
{
	class Utils {
	public:
		static size_t GetModuleBase();
		static size_t GetBaseModuleSize();
		static size_t GetBaseModuleEnd();
		static size_t FindPattern(std::string_view pattern);
		static size_t FindPattern(size_t rangeStart, size_t rangeEnd, std::string_view pattern);
		static std::string GetTypeName(void* object);
	};
}