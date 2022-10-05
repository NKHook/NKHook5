#include "SplitSprite.h"

#include "../Proj/Project.h"

#include <Files/File.h>
#include <Logging/Logger.h>
#include <Sprites/SpriteExtract.h>
#include <Sprites/Documents/SpriteTable.h>
#include <Util/Timer.h>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;
using namespace Common::Util;
using namespace DevKit;
using namespace DevKit::Features;
using namespace DevKit::Proj;
namespace fs = std::filesystem;

SplitSprite::SplitSprite() : Feature("split_sprite", "Splits a mod's vanilla spritesheet(s) into individual image files")
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
	Timer timer("SplitSprite");
	if (args.size() == 0) {
		Print(LogLevel::ERR, "No sprite file given to %s", this->GetName());
	}
	std::string modName = args[0];

	fs::path cwd = fs::current_path();
	fs::path modPath = cwd / modName;
	if (!fs::exists(modPath)) {
		Print(LogLevel::ERR, "No such mod '%s'", modName.c_str());
		return;
	}

	Project modProj;
	modProj.Open(modName);
	fs::path modDir = modProj.GetModPath();
	fs::path modTextureDir = modDir / "Textures";
	fs::path vanillaDir = modProj.GetVanillaPath();
	fs::path vanillaTextureDir = vanillaDir / "Textures";

	std::vector<fs::path> spriteSheets;
	for (auto entry : fs::directory_iterator(vanillaTextureDir)) {
		if (!entry.is_directory()) {
			spriteSheets.push_back(entry);
		}
	}

	for (fs::path spriteSheet : spriteSheets) {
		fs::path sheetFile = vanillaTextureDir / spriteSheet.filename();
		fs::path sheetDir = modTextureDir / spriteSheet.stem();
		fs::create_directories(sheetDir);

		SpriteTable* parsedTable = SpriteTable::ReadTable(sheetFile);
		/*Do extraction*/
		SpriteExtract extract(parsedTable);
		extract.SetResult(sheetDir);
		extract.ExtractAll();
	}
}
