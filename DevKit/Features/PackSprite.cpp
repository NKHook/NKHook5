#include "PackSprite.h"

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

PackSprite::PackSprite() : Feature("pack_sprite", "Pack's a mod's spritesheet(s) into full texture files")
{

}

std::string PackSprite::ActivatorArgs()
{
	return "-k, --pack, --packsprite";
}

int PackSprite::MaxArgs()
{
	return 2;
}

void PackSprite::Run(std::vector<std::string> args)
{
	Timer timer("PackSprite");
	if (args.size() == 0) {
		Print(LogLevel::ERR, "No sprite file given to %s", this->GetName());
	}
	std::string modName = args[0];
	std::string spriteName = args[1];
	
	Project modProj;
	modProj.Open(modName);
	fs::path modDir = modProj.GetModPath();
	fs::path modTextureDir = modDir / "Textures";
	fs::path vanillaDir = modProj.GetVanillaPath();
	fs::path vanillaTextureDir = vanillaDir / "Textures";
}
