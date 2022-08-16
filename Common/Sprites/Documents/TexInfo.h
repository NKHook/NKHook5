#pragma once

#include <string>

namespace Common {
	namespace Sprites {
		namespace Documents {
			enum class TexType {
				UNKNOWN,
				PNG,
				JPNG
			};

			class TexInfo {
				std::string name;
				TexType type;
			public:
				TexInfo(std::string name, TexType type);

				const std::string& GetName();
				TexType GetType();
			};
		}
	}
}