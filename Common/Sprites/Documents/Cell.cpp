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

Cell* Cell::Create(std::string name, size_t x, size_t y, size_t w, size_t h, size_t ax, size_t ay, size_t aw, size_t ah)
{
	return new Cell(name, x, y, w, h, ax, ay, aw, ah);
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

rapidxml::xml_node<>* Cell::ToXML(rapidxml::xml_document<>* document)
{
	rapidxml::xml_node<>* result = document->allocate_node(rapidxml::node_element, "Cell");
	rapidxml::xml_attribute<>* nameAttrib = document->allocate_attribute(
		"name",
		document->allocate_string(
			this->GetName().c_str()
		)
	);
	result->append_attribute(nameAttrib);
	rapidxml::xml_attribute<>* xAttrib = document->allocate_attribute(
		"x",
		document->allocate_string(
			std::to_string(this->GetX()).c_str()
		)
	);
	result->append_attribute(xAttrib);
	rapidxml::xml_attribute<>* yAttrib = document->allocate_attribute(
		"y",
		document->allocate_string(
			std::to_string(this->GetY()).c_str()
		)
	);
	result->append_attribute(yAttrib);
	rapidxml::xml_attribute<>* wAttrib = document->allocate_attribute(
		"w",
		document->allocate_string(
			std::to_string(this->GetWidth()).c_str()
		)
	);
	result->append_attribute(wAttrib);
	rapidxml::xml_attribute<>* hAttrib = document->allocate_attribute(
		"h",
		document->allocate_string(
			std::to_string(this->GetHeight()).c_str()
		)
	);
	result->append_attribute(hAttrib);
	rapidxml::xml_attribute<>* axAttrib = document->allocate_attribute(
		"ax",
		document->allocate_string(
			std::to_string(this->GetAlignedX()).c_str()
		)
	);
	result->append_attribute(axAttrib);
	rapidxml::xml_attribute<>* ayAttrib = document->allocate_attribute(
		"ay",
		document->allocate_string(
			std::to_string(this->GetAlignedY()).c_str()
		)
	);
	result->append_attribute(ayAttrib);
	rapidxml::xml_attribute<>* awAttrib = document->allocate_attribute(
		"aw",
		document->allocate_string(
			std::to_string(this->GetAlignedWidth()).c_str()
		)
	);
	result->append_attribute(awAttrib);
	rapidxml::xml_attribute<>* ahAttrib = document->allocate_attribute(
		"ah",
		document->allocate_string(
			std::to_string(this->GetAlignedHeight()).c_str()
		)
	);
	result->append_attribute(ahAttrib);
	return result;
}
