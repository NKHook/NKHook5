#pragma once

#include "../../Classes/CBloon.h"
#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5::Patches::CApplyStatusEffectTask
{
	using namespace NKHook5;

	class Fire : public IPatch
	{
		void cb_hook(Classes::CBloon* bloon, float unk, float unk2, float unk3, float unk4);
	public:
		Fire() : IPatch("CApplyStatusEffectTask::Fire") {};
		bool Apply() override;
	};
}