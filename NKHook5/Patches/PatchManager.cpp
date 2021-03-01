#include "PatchManager.h"
#include <iostream>

#include "CBloonsTD5Game/Constructor.h"

using namespace NKHook5::Patches;

void PatchManager::ApplyAll()
{
    PatchManager::ApplyPatch(new CBloonsTD5Game::Constructor());
}

void PatchManager::ApplyPatch(IPatch* toAdd)
{
    if(toAdd->Apply())
    {
        PatchManager::patches->push_back(toAdd);
        std::cout << "Successfully applied \'" << toAdd->GetName() << "\' patch!" << std::endl;
    }
    else
    {
        std::cout << "Failed to apply patch: " << toAdd->GetName() << std::endl;
    }
}