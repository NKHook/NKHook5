#pragma once

#include "CGameSystemPointers.h"

#include <vector>

namespace NKHook5::Classes {
	template<typename T>
	class ObjectManager {
	public:
		nfw::vector<T> objects;
		CGameSystemPointers* mPointers = nullptr;
	public:
		virtual ~ObjectManager() = default;
		virtual void AddObject(T* object) {};
		virtual void RemoveObject(T* object) {};
		virtual void ClearObjects() {};
		virtual void UpdateObjects() {};
		virtual void RenderObjects() {};
		virtual void SetSysPtrs(CGameSystemPointers* pointers) {};
	};
}
