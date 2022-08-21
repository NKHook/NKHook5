#pragma once

#include <deque>
#include <functional>
#include <thread>

namespace Common {
	namespace Threading {
		class WorkerThread {
			std::thread innerThread;
			std::deque<std::function<void()>> workQueue;
		public:
			WorkerThread();
			void DoWork(std::function<void()> work);
			void AwaitQueue();
		};
	}
}