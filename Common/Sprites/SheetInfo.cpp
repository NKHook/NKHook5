#include "FrameInfo.h"
#include "SheetInfo.h"
#include "SpriteCell.h"
#include <magic_enum.hpp>

#include <rapidxml.hpp>

using namespace Common;
using namespace Common::Sprites;

SheetInfo::SheetInfo(std::vector<FrameInfo> frames) {
	this->frames = frames;
}

std::shared_ptr<SheetInfo> SheetInfo::Parse(std::string data)
{
	rapidxml::xml_document<>* doc = new rapidxml::xml_document<>();
	char* dataCopy = (char*)malloc(data.size());
	memcpy_s(dataCopy, data.size(), data.data(), data.size());
	doc->parse<0>(dataCopy);

	rapidxml::xml_node<>* primaryNode = doc->first_node();
	std::string nodeName = primaryNode->name();
	if (nodeName == "FrameInformation") {
		rapidxml::xml_node<>* frameNode = primaryNode;
		std::vector<FrameInfo> framesForSheet;
		while (frameNode) {

			std::string name = "";
			TexType type = TexType::UNKNOWN;
			size_t texw = 0;
			size_t texh = 0;

			rapidxml::xml_attribute<>* frameAttrib = frameNode->first_attribute();
			while (frameAttrib) {
				std::string attribName = frameAttrib->name();

				if (attribName == "name") {
					name = frameAttrib->value();
				}
				if (attribName == "type") {
					std::string typeName = frameAttrib->value();
					if (typeName == "png") {
						type = TexType::PNG;
					}
					else if (typeName == "jpng") {
						type = TexType::JPNG;
					}
					else {
						type = TexType::UNKNOWN;
					}
				}
				if (attribName == "texw") {
					texw = std::stoi(frameAttrib->value());
				}
				if (attribName == "texh") {
					texh = std::stoi(frameAttrib->value());
				}

				frameAttrib = frameAttrib->next_attribute();
			}

			rapidxml::xml_node<>* cellNode = frameNode->first_node();
			while (cellNode) {

				//Cell attributes we need
				std::string name = "";
				size_t x = 0;
				size_t y = 0;
				size_t w = 0;
				size_t h = 0;
				size_t ax = 0;
				size_t ay = 0;
				size_t aw = 0;
				size_t ah = 0;

				rapidxml::xml_attribute<>* cellAttrib = cellNode->first_attribute();
				while (cellAttrib->next_attribute()) {
					std::string attribName = cellAttrib->name();

					if (attribName == "name") {
						name = cellAttrib->value();
					}
					if (attribName == "x") {
						x = std::stoi(cellAttrib->value());
					}
					if (attribName == "y") {
						y = std::stoi(cellAttrib->value());
					}
					if (attribName == "w") {
						w = std::stoi(cellAttrib->value());
					}
					if (attribName == "h") {
						h = std::stoi(cellAttrib->value());
					}
					if (attribName == "ax") {
						ax = std::stoi(cellAttrib->value());
					}
					if (attribName == "ay") {
						ay = std::stoi(cellAttrib->value());
					}
					if (attribName == "aw") {
						aw = std::stoi(cellAttrib->value());
					}
					if (attribName == "ah") {
						ah = std::stoi(cellAttrib->value());
					}

					cellAttrib = cellAttrib->next_attribute();
				}

				SpriteCell spriteCell(name, x, y, w, h, ax, ay, aw, ah);

				cellNode = cellNode->next_sibling();
			}

			FrameInfo frameData(name, type, texw, texh);
			framesForSheet.push_back(frameData);

			frameNode = frameNode->next_sibling();
		}

		return std::shared_ptr<SheetInfo>(new SheetInfo(framesForSheet));
	}
	if (nodeName == "SpriteInfoXml") {
		rapidxml::xml_node<>* infoNode = primaryNode;
		std::vector<XmlInfo> xmlInfos;
		while (infoNode) {
			//Info we need to get
			std::string name;
			TexType type;

			rapidxml::xml_attribute<>* infoAttrib = infoNode->first_attribute();
			while (infoAttrib) {
				std::string attribName = infoAttrib->name();
				std::string attribValue = infoAttrib->value();

				if (attribName == "name") {
					name = attribValue;
				}
				if (attribName == "type") {
					if (attribValue == "png") {
						type = TexType::PNG;
					}
					else if (attribValue == "jpng") {
						type = TexType::JPNG;
					}
					else {
						type = TexType::UNKNOWN;
					}
				}

				infoAttrib = infoAttrib->next_attribute();
			}

			infoNode = infoNode->next_sibling();
		}
		return std::shared_ptr<SheetInfo>(new SheetInfo(xmlInfos));
	}

}