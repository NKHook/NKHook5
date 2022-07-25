#include "PatchManager.h"
#include <iostream>

#include "CBasePositionableObject/Constructor.h"
#include "CBloonsTD5Game/Constructor.h"
#include "CFlagStringConvertor/FlagToString.h"
#include "CLoc/GetText.h"
#include "CSettingsScreen/InitLayout.h"
#include "OpenGL/Swapbuffers.h"
#include "Screens/GetScreenForParadigm.h"
#include "Unknown/GetDeltaLock60FPS.h"

using namespace NKHook5::Patches;

void PatchManager::ApplyAll()
{
    PatchManager::ApplyPatch(new CBasePositionableObject::Constructor());
    PatchManager::ApplyPatch(new CBloonsTD5Game::Constructor());
    PatchManager::ApplyPatch(new CFlagStringConvertor::FlagToString());
    PatchManager::ApplyPatch(new CLoc::GetText());
    PatchManager::ApplyPatch(new CSettingsScreen::InitLayout());
    PatchManager::ApplyPatch(new OpenGL::Swapbuffers());
    PatchManager::ApplyPatch(new Screens::GetScreenForParadigm());
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