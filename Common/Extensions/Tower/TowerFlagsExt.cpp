#include "TowerFlagsExt.h"

using namespace Common::Extensions::Generic;
using namespace Common::Extensions::Tower;

//Just needs to implements the flags extension for towers only
TowerFlagExt::TowerFlagExt() : FlagsExtension("TowerFlags", "Assets/JSON/TowerDefinitions/Flags.json")
{
}
