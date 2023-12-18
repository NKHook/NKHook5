#pragma once

#include "../../Classes/CTowerFactory.h"
#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5::Patches::CTowerFactory
{
	using namespace NKHook5;

	class Constructor : public IPatch
	{
		Classes::CTowerFactory* cb_hook(void* param_1, void* param_2);
	public:
		Constructor() : IPatch("CTowerFactory::Constructor")
		{

		}
		auto Apply() -> bool override;
	};
}

