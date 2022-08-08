#pragma once

#include <cstdarg>

namespace Common {
	namespace Logging {
		namespace Logger {
			enum class LogLevel {
				INFO,
				ERR,
				SUCCESS,
				DEBUG
			};

			size_t* GetCursor();
			void SetCursor(size_t x, size_t y);
			size_t Print(const char* fmt, ...);
			size_t Print(LogLevel level, const char* fmt, ...);
			size_t VPrint(LogLevel level, const char* fmt, va_list lst);
			void Progress(size_t index, size_t max, const char* fmt, ...);
		}
	}
}