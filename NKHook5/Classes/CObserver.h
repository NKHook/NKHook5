#pragma once

#include "IObserver.h"

namespace NKHook5
{
	namespace Classes
	{
		template<typename T>
		class CObserver : public IObserver
		{
			virtual void TypecheckEvent(class IEvent* e, bool& unknown) override {
				if (typeid(e) == typeid(T))
				{
					return this->HandleEvent(e);
				}
			};
			virtual void UnknownUnused(T& e) {
				return;
			};
			virtual void HandleEvent(T& e) {
				this->UnknownUnused(e);
			};
		};
	}
}