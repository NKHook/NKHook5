#include "TextureStep.h"

#include "../Util/TextureRules.h"

#include <Files/File.h>
#include <Sprites/SpritePack.h>

#include <filesystem>

using namespace Common;
using namespace Common::Files;
using namespace Common::Mod;
using namespace Common::Sprites;
using namespace DevKit;
using namespace DevKit::Packager;
using namespace DevKit::Proj;
using namespace DevKit::Util;
namespace fs = std::filesystem;

TextureStep::TextureStep() : PackageStep("Textures")
{
}

bool TextureStep::Execute(Project& proj, ZipBase& arch)
{
	fs::path modTextures = proj.GetModPath() / "Textures";
	fs::path vanillaTextures = proj.GetVanillaPath() / "Textures";

	fs::path texRules = modTextures / "Rules.json";
	File rulesFile;
	rulesFile.OpenRead(texRules);
	std::string rulesJson = rulesFile.ReadStr();
	rulesFile.Close();

	nlohmann::json parsedRules = nlohmann::json::parse(rulesJson);
	TextureRules rules(parsedRules);
	const std::vector<Compile>& texCompiles = rules.GetCompiles();
	for (const Compile& compile : texCompiles) {
		std::string sourceDir = compile.GetSourceDir();

		for (const CompileResult& result : compile.GetResults()) {
			std::string quality = result.GetQuality();
			std::string texFile = result.GetTexture();
			std::string infoXml = result.GetInfoXml();
		}
	}

	return true;
}
