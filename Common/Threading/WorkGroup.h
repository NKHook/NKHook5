#pragma once

#include "WorkerThread.h"
#include <vector>

namespace Common {
	namespace Threading {
		class WorkGroup {
			std::vector<WorkerThread*> workers;
			size_t toQNext = 0;
		public:
			WorkGroup(size_t workerCount);
			void DoWork(std::function<void()> work);
			void AwaitQueue();
			bool IsWaiting();
		};
	}
}