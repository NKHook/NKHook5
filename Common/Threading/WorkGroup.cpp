#include "WorkGroup.h"

#include <Windows.h>

using namespace Common;
using namespace Common::Threading;

WorkGroup::WorkGroup(size_t workerCount)
{
	for (size_t i = 0; i < workerCount; i++) {
		this->workers.push_back(new WorkerThread());
	}
}

void WorkGroup::DoWork(std::function<void()> work)
{
	if (toQNext >= workers.size()) {
		toQNext = 0;
	}
	this->workers[toQNext]->DoWork(work);
	toQNext++;
}

void WorkGroup::AwaitQueue()
{
	while (!IsWaiting()) {
		Sleep(10);
	}
}

bool WorkGroup::IsWaiting()
{
	bool allWaiting = true;
	for (auto& worker : this->workers) {
		if (!worker->IsWaiting()) {
			allWaiting = false;
		}
	}
	return allWaiting;
}
