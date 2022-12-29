#include "CInjectedStatusEffect.h"

#include "../Classes/CTextureLoader.h"

using namespace NKHook5;
using namespace NKHook5::Classes;
using namespace NKHook5::ClassesEx;

CInjectedStatusEffect::CInjectedStatusEffect(CTextureManager* texMgr, bool unk, float speedScale, float damageRate, float damageTimer) : CGlueStatusEffect(texMgr, unk, speedScale, damageRate, damageTimer)
{
}

CInjectedStatusEffect::~CInjectedStatusEffect()
{

}

CStatusEffect* CInjectedStatusEffect::Clone()
{
	return nullptr;
}

int CInjectedStatusEffect::TypeID()
{
	return 0;
}

void CInjectedStatusEffect::Apply()
{

}

void CInjectedStatusEffect::Reset()
{

}

void CInjectedStatusEffect::Update(SGameTime& time)
{

}

void CInjectedStatusEffect::Render()
{

}

float CInjectedStatusEffect::GetBloonSpeed(float base)
{
	return base;
}

void CInjectedStatusEffect::IncreasePops(int amount)
{
	if (this->tower != nullptr)
	{
		this->tower->IncPopCount(amount, nullptr);
	}
}