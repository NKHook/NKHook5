#pragma once

#include "../Classes/CCollectableTask.h"

namespace NKHook5::ClassesEx {
	enum class CollectMethod {
		DEFAULT,
		AUTOMATIC
	};

	class CCollectableTaskExt : public Classes::CCollectableTask {
	public:
		CollectMethod COLLECT_METHOD = CollectMethod::DEFAULT;
	};
}