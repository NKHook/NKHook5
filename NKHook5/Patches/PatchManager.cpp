#include "PatchManager.h"
#include <iostream>

#include "CApplyStatusEffectTask/Fire.h"
#include "CBaseFileIO/FileExists.h"
#include "CBaseFileIO/OpenFile.h"
#include "CBasePositionableObject/Constructor.h"
#include "CBloon/Update.h"
#include "CBloonFactory/Constructor.h"
#include "CBloonsBaseScreen/Init.h"
#include "CBloonsTD5Game/Constructor.h"
#include "CBloonsTD5Game/LoadAssets.h"
#include "CCollectableTask/Clone.h"
#include "CCollectableTask/Update.h"
#include "CFlagStringConvertor/FlagToString.h"
#include "CFlagStringConvertor/LoadCategory.h"
#include "CFlagStringConvertor/StringToFlag.h"
//#include "CGameScreen/Init.h"
#include "CLoc/FindText.h"
#include "CLoc/GetText.h"
#include "CPlayerProfileV1/InternalLoad.h"
#include "CPlayerProfileV1/Save.h"
#include "CProjectile/Clone.h"
#include "CProjectile/Update.h"
#include "CSettingsScreen/InitLayout.h"
#include "CSettingsScreen/Input.h"
#include "CSettingsScreen/Process.h"
#include "CTextureManager/GetSpriteInfoPtr.h"
#include "CTowerFactory/Constructor.h"
#include "CTowerFactory/GetTowerInfo.h"
#include "CTowerFactory/GetTowerName.h"
#include "CWeapon/Fire.h"
#include "CWeaponFactory/Constructor.h"
#include "CWeaponFactory/ParseTask.h"
#include "CZipFile/LoadFrom.h"
#include "GLRenderLayer/Draw.h"
#include "OpenGL/Swapbuffers.h"
#include "Screens/GetScreenForParadigm.h"
#include "Unknown/CrtMalloc.h"
#include "Unknown/GetDeltaLock60FPS.h"
#include "Unknown/WinMain.h"

using namespace NKHook5::Patches;

void PatchManager::ApplyAll()
{
    PatchManager::ApplyPatch(new CApplyStatusEffectTask::Fire());
    PatchManager::ApplyPatch(new CBaseFileIO::FileExists());
    PatchManager::ApplyPatch(new CBaseFileIO::OpenFile());
    PatchManager::ApplyPatch(new CBasePositionableObject::Constructor());
    PatchManager::ApplyPatch(new CBloon::Update());
    PatchManager::ApplyPatch(new CBloonFactory::Constructor());
    PatchManager::ApplyPatch(new CBloonsBaseScreen::Init());
    PatchManager::ApplyPatch(new CBloonsTD5Game::Constructor());
    PatchManager::ApplyPatch(new CBloonsTD5Game::LoadAssets());
    PatchManager::ApplyPatch(new CCollectableTask::Clone());
    PatchManager::ApplyPatch(new CCollectableTask::Update());
    PatchManager::ApplyPatch(new CFlagStringConvertor::FlagToString());
    PatchManager::ApplyPatch(new CFlagStringConvertor::LoadCategory());
    PatchManager::ApplyPatch(new CFlagStringConvertor::StringToFlag());
    //PatchManager::ApplyPatch(new CGameScreen::Init());
    PatchManager::ApplyPatch(new CLoc::FindText());
    PatchManager::ApplyPatch(new CLoc::GetText());
    PatchManager::ApplyPatch(new CPlayerProfileV1::InternalLoad());
    //PatchManager::ApplyPatch(new CPlayerProfileV1::Save());
    PatchManager::ApplyPatch(new CProjectile::Clone());
    PatchManager::ApplyPatch(new CProjectile::Update());
    PatchManager::ApplyPatch(new CSettingsScreen::InitLayout());
    //PatchManager::ApplyPatch(new CSettingsScreen::Input());
    //PatchManager::ApplyPatch(new CSettingsScreen::Process());
    PatchManager::ApplyPatch(new CTextureManager::GetSpriteInfoPtr());
    PatchManager::ApplyPatch(new CTowerFactory::Constructor());
    PatchManager::ApplyPatch(new CTowerFactory::GetTowerInfo());
    PatchManager::ApplyPatch(new CTowerFactory::GetTowerName());
    //PatchManager::ApplyPatch(new CWeapon::Fire());
    PatchManager::ApplyPatch(new CWeaponFactory::Constructor());
    PatchManager::ApplyPatch(new CWeaponFactory::ParseTask());
    PatchManager::ApplyPatch(new CZipFile::LoadFrom());
    //PatchManager::ApplyPatch(new GLRenderLayer::Draw());
    PatchManager::ApplyPatch(new OpenGL::Swapbuffers());
    PatchManager::ApplyPatch(new Screens::GetScreenForParadigm());
    PatchManager::ApplyPatch(new Unknown::CrtMalloc());
    PatchManager::ApplyPatch(new Unknown::GetDeltaLock60FPS());
    PatchManager::ApplyPatch(new Unknown::WinMain());
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