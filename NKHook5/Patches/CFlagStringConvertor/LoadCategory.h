#pragma once

#include "../../Util/NewFramework.h"
#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5::Patches::CFlagStringConvertor
{
	class LoadCategory : public IPatch
	{
		void* cb_hook(int category, nfw::string* stringList, size_t stringCount, int indexMode);

	public:
		LoadCategory() : IPatch("CFlagStringConvertor::LoadCategory")
		{

		}
		auto Apply() -> bool override;
	};
} // namespace FlagToString
        

    

