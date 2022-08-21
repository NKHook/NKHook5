#include "FrameInfo.h"
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

FrameInfo::FrameInfo() : SpriteInfo() {
	this->texW = 0;
	this->texH = 0;
	this->imagePath = "";
}

FrameInfo::FrameInfo(std::string name, TexType type, bool required) : SpriteInfo(name, type, required) {
	this->texW = 0;
	this->texH = 0;
	this->imagePath = "";
}

FrameInfo::FrameInfo(std::string name, TexType type, size_t texW, size_t texH, bool required) : SpriteInfo(name, type, required) {
	this->texW = texW;
	this->texH = texH;
	this->imagePath = "";
}

FrameInfo::FrameInfo(std::string name, TexType type, size_t texW, size_t texH, std::filesystem::path imagePath, bool required) : SpriteInfo(name, type, required) {
	this->texW = texW;
	this->texH = texH;
	this->imagePath = imagePath;
}

FrameInfo::FrameInfo(std::string name, TexType type, size_t texW, size_t texH, std::filesystem::path imagePath, std::vector<Animation*> animations, std::vector<Cell*> cells, bool required) : SpriteInfo(name, type, required) {
	this->texW = texW;
	this->texH = texH;
	this->animations = animations;
	this->cells = cells;
	this->imagePath = imagePath;
}

FrameInfo* FrameInfo::FromNode(fs::path docPath, rapidxml::xml_node<>* frameNode, std::string tableName, TexType tableType) {
	std::string frameName = "";
	size_t texW = 0;
	size_t texH = 0;
	TexType type = TexType::NONE;

	rapidxml::xml_attribute<>* frameAttrib = frameNode->first_attribute();
	while (frameAttrib) {
		std::string attribName = frameAttrib->name();
		std::string attribValue = frameAttrib->value();

		if (attribName == "name") {
			frameName = attribValue;
		}
		if (attribName == "texw") {
			texW = std::stoi(attribValue);
		}
		if (attribName == "texh") {
			texH = std::stoi(attribValue);
		}
		if (attribName == "type") {
			if (attribValue == "png") {
				type = TexType::PNG;
			}
			if (attribValue == "jpng") {
				type = TexType::JPNG;
			}
		}

		frameAttrib = frameAttrib->next_attribute();
	}

	if (frameName != tableName) {
		Print(LogLevel::WARNING, "Mismatch between the name defined in the SpriteTable and FrameInfo, returning empty FrameInfo.");
		return new FrameInfo();
	}
	if (type != tableType) {
		Print(LogLevel::WARNING, "Mismatch between the type defined in the SpriteTable and FrameInfo, returning empty FrameInfo.");
		return new FrameInfo();
	}

	fs::path qualityDir = docPath.parent_path();
	std::string fileExt = ".";
	switch (type) {
	case TexType::JPNG:
		fileExt += "jpng";
		break;
	default:
	case TexType::PNG:
		fileExt += "png";
		break;
	}
	fs::path imagePath = qualityDir / std::string(frameName + fileExt);

	rapidxml::xml_node<>* spriteNode = frameNode->first_node();
	std::vector<Animation*> resultAnims;
	std::vector<Cell*> resultCells;
	while (spriteNode) {
		std::string nodeName = spriteNode->name();
		if (nodeName == "Animation") {
			Animation* nextAnim = Animation::FromNode(spriteNode);
			resultAnims.push_back(nextAnim);
		}
		if (nodeName == "Cell") {
			Cell* nextCell = Cell::FromNode(spriteNode);
			resultCells.push_back(nextCell);
		}

		spriteNode = spriteNode->next_sibling();
	}

	return new FrameInfo(frameName, type, texW, texH, imagePath, resultAnims, resultCells);
}

size_t FrameInfo::GetTexWidth()
{
	return this->texW;
}

size_t FrameInfo::GetTexHeight()
{
	return this->texH;
}

const fs::path& FrameInfo::GetImagePath()
{
	return this->imagePath;
}

const std::vector<Animation*>& FrameInfo::GetAnimations()
{
	return this->animations;
}

const std::vector<Cell*>& FrameInfo::GetCells()
{
	return this->cells;
}
