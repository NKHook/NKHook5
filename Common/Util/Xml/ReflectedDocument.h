#pragma once

#include <rapidxml.hpp>

#include <string>

namespace Common {
	namespace Util {
		namespace Xml {
			class ReflectedDocument {
				rapidxml::xml_document<>* reflect_document = nullptr;
			public:
				ReflectedDocument();
				ReflectedDocument(std::string filter);
				~ReflectedDocument();
				void Reflect(rapidxml::xml_document<>* victim);
			};
		}
	}
}