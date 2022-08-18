#include "SplitSprite.h"
#include <Files/File.h>
#include <Graphics/CLImg.h>
#include <Graphics/GdiUtil.h>
#include <Logging/Logger.h>
#include <Sprites/Documents/SpriteTable.h>

using namespace Common;
using namespace Common::Files;
using namespace Common::Graphics;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;
using namespace Common::Sprites::Images;
using namespace DevKit;
using namespace DevKit::Features;

SplitSprite::SplitSprite() : Feature("split_sprite", "Splits a spritesheet into individual image files")
{
	
}

std::string SplitSprite::ActivatorArgs()
{
	return "-l, --split, --splitsprite";
}

int SplitSprite::MaxArgs()
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

	CLImg::SetupCL();
	Gdiplus::SetupGDI();
	SpriteTable* parsedTable = SpriteTable::ReadTable(xmlPath);
	/*Do extraction*/
	Gdiplus::StopGDI();
	CLImg::StopCL();
}
