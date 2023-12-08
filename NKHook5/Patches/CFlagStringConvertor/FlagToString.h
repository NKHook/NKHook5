#pragma once

#include "../IPatch.h"
#include "../../Utils.h"
#include "../../Util/NewFramework.h"

namespace NKHook5::Patches::CFlagStringConvertor
{
	class FlagToString : public IPatch
	{
		nfw::string cb_hook(uint32_t categoryId, uint64_t numericId);
	public:
		FlagToString() : IPatch("CFlagStringConvertor::FlagToString")
		{

		}
		auto Apply() -> bool override;
	};
} // namespace FlagToString

