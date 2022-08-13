#include "SplitSprite.h"
#include <Files/File.h>
#include <Logging/Logger.h>
#include <Sprites/FrameInfo.h>
#include <Sprites/SheetInfo.h>
#include <Sprites/SpriteCell.h>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace DevKit;
using namespace DevKit::Features;

SplitSprite::SplitSprite() : Feature("split_sprite", "Splits a spritesheet into individual image files")
{
	
}

std::string SplitSprite::ActivatorArgs()
{
	return "-l, --split, --splitsprite";
}

int  SplitSprite::MaxArgs()
{
	return 2;
}

void SplitSprite::Run(std::vector<std::string> args)
{
	if (args.size() == 0) {
		Print(LogLevel::ERR, "No sprite file given to %s", this->GetName());
	}
	std::string xmlPath = args[0];
	std::string resultPath;
	if (args.size() > 1) {
		resultPath = args[1];
	}
	File xmlFile;
	xmlFile.Open(xmlPath);
	std::string xmlData = xmlFile.ReadStr();
	std::shared_ptr<SheetInfo> sheetInfo = SheetInfo::Parse(xmlData);

	
}
