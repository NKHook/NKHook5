#pragma once

#include "CBasePositionableObject.h"
#include "CBloonEscapedEvent.h"
#include "CObserver.h"
#include "CTowerRemovedEvent.h"

#include "../Util/NewFramework.h"

namespace NKHook5::Classes
{
	class CBaseTower :
		public CBasePositionableObject,
		public CObserver<CBloonEscapedEvent>,
		public CObserver<CTowerRemovedEvent>
	{
	public:
		overload_allocators;

	public:
		char pad_00B8[12]; //0x00B8
		int32_t refCount; //0x00C4
		char pad_00C8[36]; //0x00C8
		int32_t popCount; //0x00EC
		char pad_00F0[468]; //0x00F0

	public:
		virtual ~CBaseTower() {};

		virtual void OnRemove() {};
		virtual int GetPopCount() { return this->popCount; };
		virtual void SetPopCount(int popCount) { this->popCount = popCount; };
		virtual void IncPopCount(int amount, class CBloon* bloon) {};
		virtual void KONG_FUN_00633bb0() {};
	};

	static_assert(sizeof(CObserver<CBloonEscapedEvent>) == 0x8);
	static_assert(sizeof(CObserver<CTowerRemovedEvent>) == 0x8);
	//static_assert(sizeof(CBaseTower) == 0x2C4);
} // namespace NKHook5::Classes

