#include "WorkerThread.h"

#include <Windows.h>

#include "../Logging/Logger.h"

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Threading;

WorkerThread::WorkerThread() {
	this->innerThread = nullptr;
}

WorkerThread::~WorkerThread() {
	if(this->innerThread != nullptr)
		delete this->innerThread;
}

void WorkerThread::DoWork(std::function<void()> work)
{
	if (this->innerThread == nullptr) {
		try {
			this->innerThread = new std::thread([&] {
				while (true) {
					lock.lock();
					if (workQueue.empty()) {
						lock.unlock();
						Sleep(10);
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
		catch (std::exception& ex)
		{
			Sleep(1000);
			this->DoWork(work);
		}
	}
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