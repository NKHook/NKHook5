#include "XmlInfo.h"

using namespace Common;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

XmlInfo::XmlInfo(std::string name, TexType type, bool required) : TexInfo(name, type) {
	this->required = required;
}