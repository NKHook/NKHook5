#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5
{
	namespace Patches
	{
		namespace CApplyStatusEffectTask
		{
			class Fire : public IPatch
			{
			public:
				Fire() : IPatch("CApplyStatusEffectTask::Fire") {};
				bool Apply() override;
			};
		}
	}
}