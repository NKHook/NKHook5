#include "XmlInfo.h"

using namespace Common;
using namespace Common::Sprites;

XmlInfo::XmlInfo(std::string name, TexType type, bool required) : TexInfo(name, type) {
	this->required = required;
}