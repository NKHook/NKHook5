#pragma once

#include "ITowerStatModifier.h"

#include <vector>

namespace NKHook5::Classes
{
	class CModifierStack : public ITowerStatModifier
	{
	public:
		std::vector<class CModifier*> mModifiers; //0x0004
		class CBaseTower* mProbablyFactoryTower = nullptr;

		~CModifierStack() override = default;
	};
}