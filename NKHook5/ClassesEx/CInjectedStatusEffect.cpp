#include "CInjectedStatusEffect.h"

#include "../Classes/CAnimationSystem.h"

#include "../Util/NewFramework.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

using namespace NKHook5;
using namespace NKHook5::Classes;
using namespace NKHook5::ClassesEx;

static CStatusEffect* __fastcall STATIC_Clone(CInjectedStatusEffect* self)
{
	auto* clone = new CInjectedStatusEffect(self->mInjectedId, self->mGraphicName, self->mExceptMoab, self->mTexMgr, self->mDamageInterval, self->mDamageTimer, self->mSpeedScale);
	return reinterpret_cast<CStatusEffect*>(clone);
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
	Classes::CCompoundSprite* sprite = self;
	auto compoundInfo = self->mTexMgr->LoadCompound("Assets/JSON/BloonSprites/", self->mGraphicName);
	sprite->Load(compoundInfo, true, true);
	sprite->SetXY({ 0, 0 });
	sprite->ScaleXY({ 1, 1 });

	self->mAnimationSystem->mPlayMode = 2;
}

static float __fastcall STATIC_GetBloonSpeed(CInjectedStatusEffect* self, void* pad, float base)
{
	return self->mSpeedScale * base;
}

CInjectedStatusEffect::CInjectedStatusEffect(uint64_t injectedId, nfw::string graphicName, bool exceptMoab, CTextureManager* texMgr, float damageInterval, float duration, float speedScale)
	: CNapalmStatusEffect(texMgr, damageInterval, 0.0f)
{
	//Get the vtables here
	void* pVanillaVTable = (void*)Signatures::GetAddressOf(Sigs::CNapalmStatusEffect_VTable);
	this->mpVanillaVTable = static_cast<void**>(pVanillaVTable);

	void*** ppCustomVTable = (void***)this;

	//Change our vtable's protection (the 33 is the num of virtual funcs)
	DWORD oprot = 0;
	VirtualProtect(*ppCustomVTable, sizeof(size_t) * CNapalmStatusEffect_VFuncCount, PAGE_EXECUTE_READWRITE, &oprot);

	//Write the vanilla vtable to our custom vtable
	memcpy(*ppCustomVTable, pVanillaVTable, sizeof(size_t) * CNapalmStatusEffect_VFuncCount);

	//Place back the funcs we dont want replaced
	(*ppCustomVTable)[1] = &STATIC_Clone;
	(*ppCustomVTable)[2] = &STATIC_TypeID;
	(*ppCustomVTable)[3] = &STATIC_Apply;
	(*ppCustomVTable)[7] = &STATIC_GetBloonSpeed;

	CSprite* napalmSprite = static_cast<CNapalmStatusEffect*>(this);
	*(void**)napalmSprite = (void*)Signatures::GetAddressOf(Sigs::CSprite_VTable);

	//Now we have our own vtable overridden by the game's vtable, and we are free to make changes.
	this->mDuration = duration;
	this->mTimer = duration;
	this->mSpeedScale = speedScale;
	this->mInjectedId = injectedId;
	this->mGraphicName = graphicName;
	this->mExceptMoab = exceptMoab;
}