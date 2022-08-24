#include "Timer.h"
#include "../Logging/Logger.h"

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Util;
namespace ch = std::chrono;

Timer::Timer(std::string funcName) {
	this->funcName = funcName;
	this->startTime = ch::system_clock::now();
	Print("Began %s", funcName.c_str());
}

Timer::~Timer() {
	ch::duration<float> diff = ch::system_clock::now() - this->startTime;
	Print("%s completed (%.2f s)", funcName.c_str(), diff.count());
}