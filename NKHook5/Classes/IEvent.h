#pragma once

namespace NKHook5
{
	namespace Classes
	{
		class IEvent
		{
		public:
			virtual ~IEvent()
			{

			}
			virtual bool PersistsIfQueued() const
			{
				return false;
			}
		};
	}
}