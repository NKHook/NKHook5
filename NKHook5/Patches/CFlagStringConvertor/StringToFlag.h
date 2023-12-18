#pragma once

#include "../../Util/NewFramework.h"
#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5::Patches::CFlagStringConvertor
{
	class StringToFlag : public IPatch
	{
		uint64_t cb_hook(int categoryId, nfw::string* textId);
	public:
		StringToFlag() : IPatch("CFlagStringConvertor::StringToFlag")
		{

		}
		auto Apply() -> bool override;
	};
} // namespace FlagToString