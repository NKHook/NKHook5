#pragma once

#include "../../Util/NewFramework.h"

namespace NKHook5 {
	namespace Classes {
		class IInput {
		public:
			overload_new

		public:
			virtual ~IInput() {};
			virtual void FirstTouch(void* param_1, void* param_2) {};
			virtual void ContinuedTouch(void* param_1, void* param_2) {};
			virtual void TouchReleased(void* param_1, void* param_2) {};
			virtual void TouchTerminated(void* param_1, void* param_2) {};
			virtual void TouchCancelled(void* param_1, void* param_2) {};
			virtual void KeyPressed(void* param_1, void* param_2) {};
			virtual void ResetInput(void* param_1, void* param_2) {};
			virtual void ResetPlayerInput(void* param_1, void* param_2) {};
			virtual void Scrolling(void* param_1, void* param_2) {};
		};
	}
}