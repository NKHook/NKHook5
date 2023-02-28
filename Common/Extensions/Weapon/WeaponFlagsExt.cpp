#include "WeaponFlagsExt.h"

using namespace Common::Extensions::Generic;
using namespace Common::Extensions::Weapon;

//Just needs to implements the flags extension for towers only
WeaponFlagsExt::WeaponFlagsExt() : FlagsExtension("WeaponFlags", "Assets/JSON/WeaponDefinitions/Flags.json")
{
}
