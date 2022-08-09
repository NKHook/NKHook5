#pragma once

#include "CGameSystemPointers.h"

#include <vector>

namespace NKHook5 {
	namespace Classes {
		template<typename T>
		class ObjectManager {
		public:
			std::vector<T> objects;
			CGameSystemPointers* pointers;
		public:
			virtual ~ObjectManager() {};
			virtual void AddObject(T* object) {};
			virtual void RemoveObject(T* object) {};
			virtual void ClearObjects() {};
			virtual void UpdateObjects() {};
			virtual void RenderObjects() {};
			virtual void SetSysPtrs(CGameSystemPointers* pointers) {};
		};
	}
}