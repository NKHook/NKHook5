#include "StatusFlagsExt.h"

#include "../ExtensionManager.h"
#include <Files/File.h>

using namespace Common::Extensions::Generic;
using namespace Common::Extensions::StatusEffect;
namespace fs = std::filesystem;

//Just needs to implements the flags extension for towers only
StatusFlagsExt::StatusFlagsExt() : FlagsExtension("StatusFlags", "Assets/JSON/StatusDefinitions/Flags.json")
{
}