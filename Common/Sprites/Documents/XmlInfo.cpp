#include "XmlInfo.h"

using namespace Common;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

XmlInfo::XmlInfo() : SpriteInfo() {
	this->image = nullptr;
}

XmlInfo::XmlInfo(std::string name, TexType type, bool required) : SpriteInfo(name, type, required) {
	this->image = nullptr;
}

XmlInfo::XmlInfo(std::string name, TexType type, std::vector<Animation> animations, std::vector<Cell> cells, bool required) : SpriteInfo(name, type, required) {
	this->animations = animations;
	this->cells = cells;
	this->image = nullptr;
}

XmlInfo::XmlInfo(std::string name, TexType type, std::vector<Animation> animations, std::vector<Cell> cells, BitmapImage* image, bool required) : SpriteInfo(name, type, required) {
	this->animations = animations;
	this->cells = cells;
	this->image = image;
}