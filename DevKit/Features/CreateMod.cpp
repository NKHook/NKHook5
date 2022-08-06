#include "CreateMod.h"

using namespace DevKit;
using namespace DevKit::Features;

CreateMod::CreateMod() : Feature("create_mod", "Create a new mod with a given name") {

}

std::string CreateMod::ActivatorArgs()
{
	return "-c, --create-mod";
}

void CreateMod::Run(std::vector<std::string> args) {
	
}