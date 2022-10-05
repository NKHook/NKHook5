#include "SpritePack.h"

using namespace Common;
using namespace Common::Sprites;
namespace fs = std::filesystem;

SpritePack::SpritePack(SpriteTable* table)
{
	this->table = table;
}

void SpritePack::SetResult(fs::path resultDir)
{
	this->resultDir = resultDir;
}

void SpritePack::PackAll()
{
}
