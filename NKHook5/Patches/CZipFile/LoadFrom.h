#pragma once

#include "../IPatch.h"
#include "../../Utils.h"

namespace NKHook5 {
	namespace Patches {
		namespace CZipFile {
            class LoadFrom : public IPatch
            {
            public:
                LoadFrom() : IPatch("CZipFile::LoadFrom")
                {

                }
                auto Apply() -> bool override;
            };
		}
	}
}