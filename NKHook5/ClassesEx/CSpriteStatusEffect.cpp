#include "CSpriteStatusEffect.h"

using namespace NKHook5;
using namespace NKHook5::Classes;
using namespace NKHook5::ClassesEx;

CSpriteStatusEffect::CSpriteStatusEffect() : CStatusEffect()
{

}

CSpriteStatusEffect::~CSpriteStatusEffect()
{

}

CStatusEffect* CSpriteStatusEffect::Clone()
{
	return nullptr;
}

int CSpriteStatusEffect::TypeID()
{
	return 0;
}

void CSpriteStatusEffect::Apply()
{

}

void CSpriteStatusEffect::Reset()
{

}

void CSpriteStatusEffect::Update(SGameTime& time)
{

}

void CSpriteStatusEffect::Render()
{

}

float CSpriteStatusEffect::GetBloonSpeed(float base)
{
	return base;
}

void CSpriteStatusEffect::IncreasePops(int amount)
{
	if (this->tower != nullptr)
	{
		this->tower->IncPopCount(amount, nullptr);
	}
}