#include "TexInfo.h"

using namespace Common;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

TexInfo::TexInfo(std::string name, TexType type) {
	this->name = name;
	this->type = type;
}

const std::string& TexInfo::GetName() {
	return this->name;
}

TexType TexInfo::GetType() {
	return this->type;
}