#pragma once

namespace NKHook5
{
	namespace Classes
	{
		class IEvent
		{
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