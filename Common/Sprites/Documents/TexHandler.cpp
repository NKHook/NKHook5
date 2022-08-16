#include "TexHandler.h"
#include "../../Files/File.h"

using namespace Common;
using namespace Common::Files;
using namespace Common::Sprites;
using namespace Common::Sprites::Documents;

TexHandler::TexHandler() {
	File spriteInfoFile;
	File fullSpriteInfoFile;
	File extraSpriteInfoFile;

	spriteInfoFile.Open("SpriteInfo.xml");
	fullSpriteInfoFile.Open("FullSpriteInfo.xml");
	extraSpriteInfoFile.Open("ExtraSpriteInfo.xml");

	this->spriteInfo = SheetInfo::Parse(spriteInfoFile.ReadStr());
	this->fullSpriteInfo = SheetInfo::Parse(fullSpriteInfoFile.ReadStr());
	this->extraSpriteInfo = SheetInfo::Parse(extraSpriteInfoFile.ReadStr());
}

static TexHandler* instance;
TexHandler* TexHandler::GetInstance() {
	if (!instance) {
		instance = new TexHandler();
	}
	return instance;
}