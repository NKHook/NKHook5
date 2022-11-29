#pragma once

#include "IEvent.h"

namespace NKHook5
{
	namespace Classes
	{
		class IObserver
		{
		public:
			void* manager = nullptr;

			virtual ~IObserver() {};
			virtual void TypecheckEvent(IEvent* e, bool& unknown) {};
			virtual void ManagerDestroyed() {
				this->manager = nullptr;
			};
		};
	}
}