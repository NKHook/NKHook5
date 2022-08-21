#pragma once

#include <string>

namespace Common {
	namespace Sprites {
		namespace Documents {
			class InfoBase {
				std::string name;
				InfoBase* parent;
			public:
				InfoBase();
				InfoBase(std::string);
				virtual void SetParent(InfoBase*);
				virtual InfoBase* GetParent();
				const std::string& GetName();
			};
		}
	}
}