#pragma once

#include <deque>
#include <functional>
#include <thread>
#include <mutex>

namespace Common {
	namespace Threading {
		class WorkerThread {
			std::thread* innerThread;
			std::deque<std::function<void()>> workQueue;
			std::mutex lock;
		public:
			WorkerThread();
			~WorkerThread();
			void DoWork(std::function<void()> work);
			void AwaitQueue();
			bool IsWaiting();
		};
	}
}