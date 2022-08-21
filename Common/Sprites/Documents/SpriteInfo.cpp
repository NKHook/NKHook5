#include "SpriteInfo.h"

using namespace Common;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

SpriteInfo::SpriteInfo() : InfoBase() {
	this->type = TexType::NONE;
	this->required = true;
}

SpriteInfo::SpriteInfo(std::string name, TexType type, bool required) : InfoBase(name) {
	this->type = type;
	this->required = required;
}

TexType SpriteInfo::GetTexType()
{
	return this->type;
}

bool SpriteInfo::IsRequired()
{
	return this->required;
}
