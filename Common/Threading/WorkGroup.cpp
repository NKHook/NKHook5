#include "WorkGroup.h"

#include <Windows.h>

using namespace Common;
using namespace Common::Threading;

WorkGroup::WorkGroup(size_t workerCount)
{
	this->workers = std::vector<WorkerThread>(workerCount);
}

void WorkGroup::DoWork(std::function<void()> work)
{
	for (auto& worker : this->workers) {
		if (worker.IsWaiting()) {
			worker.DoWork(work);
			return;
		}
	}
	this->workers[0].DoWork(work);
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
		if (!worker.IsWaiting()) {
			allWaiting = false;
		}
	}
	return allWaiting;
}
