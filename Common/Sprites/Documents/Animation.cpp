#include "Animation.h"

using namespace Common;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

Animation::Animation() : InfoBase() {
	this->animCells = std::vector<Cell>();
}

Animation::Animation(std::string name) : InfoBase(name) {
	this->animCells = std::vector<Cell>();
}

Animation::Animation(std::string name, std::vector<Cell> cells) : InfoBase(name) {
	this->animCells = cells;
}