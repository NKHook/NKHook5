#include "WorkerThread.h"

#include <Windows.h>

using namespace Common;
using namespace Common::Threading;

WorkerThread::WorkerThread() {
	this->innerThread = std::thread([&] {
		while (true) {
			if (workQueue.empty()) {
				Sleep(100);
				continue;
			}

			std::function<void()> nextJob = workQueue.front();
			nextJob();
			workQueue.pop_front();
		}
	});
}

void WorkerThread::DoWork(std::function<void()> work)
{
	this->workQueue.push_back(work);
}

void WorkerThread::AwaitQueue() {
	while (!this->workQueue.empty()) {
		Sleep(10);
	}
}