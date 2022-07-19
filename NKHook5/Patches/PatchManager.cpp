#include "PatchManager.h"
#include <iostream>

#include "CBasePositionableObject/Constructor.h"
#include "CBloonsTD5Game/Constructor.h"
#include "CLoc/GetLoc.h"
#include "Unknown/GetDeltaLock60FPS.h"

using namespace NKHook5::Patches;

void PatchManager::ApplyAll()
{
    PatchManager::ApplyPatch(new CBasePositionableObject::Constructor());
    PatchManager::ApplyPatch(new CBloonsTD5Game::Constructor());
    PatchManager::ApplyPatch(new CLoc::GetLoc());
    PatchManager::ApplyPatch(new Unknown::GetDeltaLock60FPS());
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