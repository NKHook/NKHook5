#include "InfoBase.h"

using namespace Common;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

InfoBase::InfoBase() {
	this->name = "";
	this->parent = nullptr;
}
InfoBase::InfoBase(std::string name) {
	this->name = name;
	this->parent = nullptr;
}

void InfoBase::SetParent(InfoBase* parent) {
	this->parent = parent;
}

InfoBase* InfoBase::GetParent() {
	return this->parent;
}

const std::string& InfoBase::GetName()
{
	return this->name;
}
