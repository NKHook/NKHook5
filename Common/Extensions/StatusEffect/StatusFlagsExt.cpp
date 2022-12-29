#include "StatusFlagsExt.h"

using namespace Common::Extensions::Generic;
using namespace Common::Extensions::StatusEffect;

//Just needs to implements the flags extension for towers only
StatusFlagExt::StatusFlagExt() : FlagsExtension("StatusFlags", "Assets/JSON/StatusDefinitions/Flags.json")
{
}
