#pragma once

namespace NKHook5
{
	namespace Classes
	{
		class IObserver
		{
			void* manager = nullptr;

			virtual ~IObserver() {};
			virtual void TypecheckEvent(class IEvent* e, bool& unknown) {};
			virtual void ManagerDestroyed() {
				this->manager = nullptr;
			};
		};
	}
}