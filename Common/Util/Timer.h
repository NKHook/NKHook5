#pragma once

#include <chrono>
#include <string>
#include <stdint.h>

namespace Common {
	namespace Util {
		class Timer {
			std::chrono::system_clock::time_point startTime;
			std::string funcName;
		public:
			Timer(std::string funcName);
			~Timer();
		};
	}
}