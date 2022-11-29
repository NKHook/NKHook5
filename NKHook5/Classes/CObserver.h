#pragma once

#include "IObserver.h"

namespace NKHook5
{
	namespace Classes
	{
		template<typename T>
		class CObserver : public IObserver
		{
		public:
			virtual ~CObserver() {};
			virtual void TypecheckEvent(IEvent* e, bool& unknown) override {
				if (typeid(e) == typeid(T))
				{
					return this->TypesafeHandleEvent((T*)e);
				}
			};
			virtual void HandleEvent(T* e) {
				return;
			};
			virtual void TypesafeHandleEvent(T* e) {
				this->HandleEvent(e);
			};
		};
	}
}