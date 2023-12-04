#pragma once

#include "IObserver.h"

#include <typeinfo>

namespace NKHook5::Classes
{
	template<typename T>
	class CObserver : public IObserver
	{
	public:
		~CObserver() override = default;
		void TypecheckEvent(IEvent* e, bool& unknown) override {
			if (typeid(e) == typeid(T))
			{
				return this->TypesafeHandleEvent((T*)e);
			}
		};
		virtual void HandleEvent(T* e) {};
		virtual void TypesafeHandleEvent(T* e) {
			this->HandleEvent(e);
		};
	};
}