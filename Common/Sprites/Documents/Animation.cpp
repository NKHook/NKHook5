#include "Animation.h"
#include "../../Logging/Logger.h"

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

Animation::Animation() : InfoBase() {
	this->animCells = std::vector<Cell*>();
	this->fullImage = nullptr;
}

Animation::Animation(std::string name) : InfoBase(name) {
	this->animCells = std::vector<Cell*>();
	this->fullImage = nullptr;
}

Animation::Animation(std::string name, std::vector<Cell*> cells) : InfoBase(name) {
	this->animCells = cells;
	this->fullImage = nullptr;
}

Animation::Animation(std::string name, std::vector<Cell*> cells, BitmapImage* fullImage) : InfoBase(name) {
	this->animCells = cells;
	this->fullImage = fullImage;
}

Animation* Animation::FromNode(rapidxml::xml_node<>* animNode, BitmapImage* fullImage) {
	rapidxml::xml_attribute<>* nextAttrib = animNode->first_attribute();

	/* Read the animation name */
	std::string animName;
	while (nextAttrib) {
		std::string attribName = nextAttrib->name();
		std::string attribValue = nextAttrib->value();

		if (attribName == "name") {
			animName = attribValue;
		}

		nextAttrib = nextAttrib->next_attribute();
	}
	if (animName.empty()) {
		Print(LogLevel::WARNING, "animName was empty for an Animation... An empty Animation will be returned");
		return new Animation();
	}

	/* Read the animation frames as cells */
	rapidxml::xml_node<>* nextNode = animNode->first_node();
	std::vector<Cell*> animCells;
	while (nextNode) {

		animCells.push_back(Cell::FromNode(nextNode, fullImage));

		nextNode = nextNode->next_sibling();
	}

	return new Animation(animName, animCells, fullImage);
}