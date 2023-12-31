#include "CInjectedStatusEffect.h"

#include "../Classes/CTextureLoader.h"

#include "../Util/NewFramework.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace NKHook5;
using namespace NKHook5::Classes;
using namespace NKHook5::ClassesEx;

static CStatusEffect* __fastcall STATIC_Clone(CInjectedStatusEffect* self)
{
	CInjectedStatusEffect* clone = new CInjectedStatusEffect(self->mInjectedId, self->mSpriteInfo, self->mTexture, self->mExceptMoab, self->mTexMgr, false, self->mSpeedScale, self->mDamageRate);
	return clone;
}

static uint64_t __fastcall STATIC_TypeID(CInjectedStatusEffect* self)
{
	return self->mInjectedId;
}

static void __fastcall STATIC_Apply(CInjectedStatusEffect* self)
{
	auto* mfApply = reinterpret_cast<void(__thiscall*)(CInjectedStatusEffect*)>(self->mpVanillaVTable[3]);
	mfApply(self);

	//Change the sprite to the custom sprite
	Classes::CSprite* sprite = self;
	auto spriteInfo = self->mTexMgr->GetSpriteInfoPtr(self->mTexture, self->mSpriteInfo);
	sprite->SetTexture(spriteInfo, false);
	sprite->SetXY({ 0, 0 });
	sprite->ScaleXY({ 1.25, 1.25 });
}

static void __fastcall STATIC_Render(CInjectedStatusEffect* self, void* pad, SGameTime& time)
{
	CSprite* selfSprite = self;
	selfSprite->Render(true);
}

CInjectedStatusEffect::CInjectedStatusEffect(uint64_t injectedId, std::string spriteInfo, std::string texture, bool exceptMoab, CTextureManager* texMgr, bool detach, float speedScale, float damageRate, float damageTimer)
	: CGlueStatusEffect(texMgr, detach, speedScale, damageRate, damageTimer)
{
	//Get the vtables here
	void* pVanillaVTable = (void*)Signatures::GetAddressOf(Sigs::CGlueStatusEffect_VTable);
	this->mpVanillaVTable = static_cast<void**>(pVanillaVTable);

	void*** ppCustomVTable = (void***)this;

	//Change our vtable's protection (the 33 is the num of virtual funcs)
	DWORD oprot = 0;
	VirtualProtect(*ppCustomVTable, sizeof(size_t) * CGlueStatusEffect_VFuncCount, PAGE_EXECUTE_READWRITE, &oprot);

	//Write the vanilla vtable to our custom vtable
	memcpy(*ppCustomVTable, pVanillaVTable, sizeof(size_t) * CGlueStatusEffect_VFuncCount);

	//Place back the funcs we dont want replaced
	(*ppCustomVTable)[1] = &STATIC_Clone;
	(*ppCustomVTable)[2] = &STATIC_TypeID;
	(*ppCustomVTable)[3] = &STATIC_Apply;
	//(*ppCustomVTable)[6] = &STATIC_Render;

	CSprite* selfSprite = this;
	*(void**)selfSprite = (void*)Signatures::GetAddressOf(Sigs::CSprite_VTable);

	//Now we have our own vtable overridden by the game's vtable, and we are free to make changes.
	this->mInjectedId = injectedId;
	this->mSpriteInfo = spriteInfo;
	this->mTexture = texture;
}