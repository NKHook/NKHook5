#include "SpriteTable.h"
#include "../../Files/File.h"
#include "../../Logging/Logger.h"

#include <rapidxml.hpp>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;
using namespace Common::Sprites::Images;
namespace fs = std::filesystem;

SpriteTable::SpriteTable() {

}

SpriteTable::SpriteTable(std::vector<XmlInfo*> spriteXmls) {
	this->spriteXmls = spriteXmls;
}

SpriteTable* SpriteTable::ReadTable(fs::path path) {
	File tableFile;
	tableFile.OpenRead(path);
	std::string xmlContent = tableFile.ReadStr();

	auto* xmlDocument = new rapidxml::xml_document<>();
	xmlDocument->parse<0>((char*)xmlContent.c_str());

	rapidxml::xml_node<>* infoNode = xmlDocument->first_node();
	if (!infoNode) {
		Print(LogLevel::ERR, "No SpriteInformation node? strange... an empty SpriteTable will be returned.");
		return new SpriteTable();
	}
	rapidxml::xml_node<>* xmlNode = infoNode->first_node();
	std::vector<XmlInfo*> results;
	fs::path texDir = path.parent_path();
	while (xmlNode) {
		std::string name = "";
		TexType type = TexType::NONE;

		rapidxml::xml_attribute<>* attrib = xmlNode->first_attribute();
		while (attrib) {
			std::string attribName = attrib->name();
			std::string attribValue = attrib->value();

			if (attribName == "name") {
				name = attribValue;
			}
			if (attribName == "type") {
				if (attribValue == "png") {
					type = TexType::PNG;
				}
				if (attribValue == "jpng") {
					type = TexType::JPNG;
				}
			}

			attrib = attrib->next_attribute();
		}

		fs::path sheetFile = texDir / "Ultra" / fs::path(name + ".xml");
		XmlInfo* newInfo = XmlInfo::ReadDoc(sheetFile, name, type);
		results.push_back(newInfo);

		xmlNode = xmlNode->next_sibling();
	}

	return new SpriteTable(results);
}