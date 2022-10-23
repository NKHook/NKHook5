#pragma once

#include "../../Util/Glob.h"
#include "../JsonExtension.h"
#include <vector>

namespace Common {
	namespace Extensions {
		namespace Generic {
			using namespace Common;
			using namespace Common::Extensions;
			using namespace Common::Extensions::Generic;
			using namespace Common::Util;

			class MergeIgnoreExtension : public JsonExtension {
				std::vector<Glob> ignoreGlobs;
			public:
				MergeIgnoreExtension();
				virtual bool IsCustomDocument();
				virtual void UseJsonData(nlohmann::json content);
				virtual const std::vector<Glob>& GetIgnores();
			};
		}
	}
}