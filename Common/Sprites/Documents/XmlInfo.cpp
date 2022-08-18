#include "XmlInfo.h"
#include "../../Files/File.h"
#include "../../Files/PngPhoto.h"
#include "../../Logging/Logger.h"

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;
namespace fs = std::filesystem;

XmlInfo::XmlInfo() : SpriteInfo() {}

XmlInfo::XmlInfo(std::string name, TexType type) : SpriteInfo(name, type) {}

XmlInfo::XmlInfo(std::string name, TexType type, std::vector<FrameInfo*> frames) : SpriteInfo(name, type) {
	this->frames = frames;
}

XmlInfo* XmlInfo::ReadDoc(fs::path path, std::string tableName, TexType tableType) {
	File docFile;
	docFile.OpenRead(path);
	std::string docContent = docFile.ReadStr();
	auto* xmlDoc = new rapidxml::xml_document<>();
	xmlDoc->parse<0>((char*)docContent.c_str());

	rapidxml::xml_node<>* spriteInfo = xmlDoc->first_node();
	if (!spriteInfo) {
		Print(LogLevel::WARNING, "An XmlInfo document cannot be read as there are no nodes! Returning empty XmlInfo...");
		return new XmlInfo();
	}
	if (std::string(spriteInfo->name()) != std::string("SpriteInformation")) {
		Print(LogLevel::ERR, "The first node in an XmlInfo was not 'SpriteInformation', returning empty XmlInfo");
		return new XmlInfo();
	}

	rapidxml::xml_node<>* frameNode = spriteInfo->first_node();
	std::vector<FrameInfo*> resultFrames;
	while (frameNode) {
		FrameInfo* frame = FrameInfo::FromNode(path, frameNode, tableName, tableType);
		resultFrames.push_back(frame);

		frameNode = frameNode->next_sibling();
	}
	return new XmlInfo(tableName, tableType, resultFrames);
}