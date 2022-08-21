#include "WorkerThread.h"

#include <Windows.h>

using namespace Common;
using namespace Common::Threading;

WorkerThread::WorkerThread() {
	this->innerThread = new std::thread([&] {
		while (true) {
			lock.lock();
			if (workQueue.empty()) {
				lock.unlock();
				Sleep(100);
				continue;
			}

			std::function<void()> nextJob = workQueue.front();
			nextJob();
			workQueue.pop_front();
			lock.unlock();
		}
	});
	this->innerThread->detach();
}

WorkerThread::~WorkerThread() {
	delete this->innerThread;
}

void WorkerThread::DoWork(std::function<void()> work)
{
	this->lock.lock();
	this->workQueue.push_back(work);
	this->lock.unlock();
}

void WorkerThread::AwaitQueue() {
	while (!this->IsWaiting()) {
		Sleep(10);
	}
}

bool WorkerThread::IsWaiting() {
	this->lock.lock();
	bool isWaiting = this->workQueue.empty();
	this->lock.unlock();
	return isWaiting;
}