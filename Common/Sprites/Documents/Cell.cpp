#include "Cell.h"

using namespace Common;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

Cell::Cell() : InfoBase() {
	this->x = 0;
	this->y = 0;
	this->w = 0;
	this->h = 0;
	this->ax = 0;
	this->ay = 0;
	this->aw = 0;
	this->ah = 0;
}

Cell::Cell(std::string name,
	size_t x,
	size_t y,
	size_t w,
	size_t h,
	size_t ax,
	size_t ay,
	size_t aw,
	size_t ah) : InfoBase(name)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->ax = ax;
	this->ay = ay;
	this->aw = aw;
	this->ah = ah;
}

Cell* Cell::FromNode(rapidxml::xml_node<>* cellNode)
{
	//We only need to read cell attributes
	//I can't find an example where Cells have child nodes
	//If only NK publicly released specs for all the formats for these games
	//would make it so much easier to implement, but they hate modding, so :(
	//NK pls hire me I'd be great for your PR team & Development team I promise

	std::string cellName;
	size_t cellX = 0;
	size_t cellY = 0;
	size_t cellW = 0;
	size_t cellH = 0;
	size_t cellAx = 0;
	size_t cellAy = 0;
	size_t cellAw = 0;
	size_t cellAh = 0;

	rapidxml::xml_attribute<>* nextAttrib = cellNode->first_attribute();
	while (nextAttrib) {
		std::string attribName = nextAttrib->name();
		std::string attribValue = nextAttrib->value();

		if (attribName == "name") {
			cellName = attribValue;
		}
		if (attribName == "x") {
			cellX = std::stoi(attribValue);
		}
		if (attribName == "y") {
			cellY = std::stoi(attribValue);
		}
		if (attribName == "w") {
			cellW = std::stoi(attribValue);
		}
		if (attribName == "h") {
			cellH = std::stoi(attribValue);
		}
		if (attribName == "ax") {
			cellAx = std::stoi(attribValue);
		}
		if (attribName == "ay") {
			cellAy = std::stoi(attribValue);
		}
		if (attribName == "aw") {
			cellAw = std::stoi(attribValue);
		}
		if (attribName == "ah") {
			cellAh = std::stoi(attribValue);
		}

		nextAttrib = nextAttrib->next_attribute();
	}

	return new Cell(cellName, cellX, cellY, cellW, cellH, cellAx, cellAy, cellAw, cellAh);
}

size_t Cell::GetX()
{
	return this->x;
}
size_t Cell::GetY()
{
	return this->y;
}
size_t Cell::GetWidth()
{
	return this->w;
}
size_t Cell::GetHeight()
{
	return this->h;
}
size_t Cell::GetAlignedX()
{
	return this->ax;
}
size_t Cell::GetAlignedY()
{
	return this->ay;
}
size_t Cell::GetAlignedWidth()
{
	return this->aw;
}
size_t Cell::GetAlignedHeight()
{
	return this->ah;
}