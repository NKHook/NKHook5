#include "StringToFlag.h"

#include "../../Util/NewFramework.h"
#include "../../Classes/CBloonFactory.h"
#include "../../Classes/CTowerFactory.h"
#include "../../Classes/CFlagStringConvertor.h"
#include "../../Classes/CWeaponFactory.h"
#include "../../Signatures/Signature.h"
#include "../../Util/FlagManager.h"

extern NKHook5::Classes::CTowerFactory* g_towerFactory;
extern NKHook5::Util::FlagManager g_towerFlags;
extern NKHook5::Classes::CBloonFactory* g_bloonFactory;
extern NKHook5::Util::FlagManager g_bloonFlags;
extern NKHook5::Util::FlagManager g_bloonStatusFlags;
extern NKHook5::Classes::CWeaponFactory* g_weaponFactory;
extern NKHook5::Util::FlagManager g_weaponFlags;

namespace NKHook5::Patches::CFlagStringConvertor
{
	using namespace Signatures;

	static uint64_t o_func;
	uint64_t StringToFlag::cb_hook(int categoryId, nfw::string* textId) {
		auto* self = reinterpret_cast<Classes::CFlagStringConvertor*>(this);

		auto ofn = std::bit_cast<decltype(&StringToFlag::cb_hook)>(reinterpret_cast<void*>(o_func));
		uint64_t result = (this->*ofn)(categoryId, textId);

		if (self == g_towerFactory) {
			if (categoryId == 0) {
				result = g_towerFlags.GetFlag(std::string(*textId));
			}
		}

		if (self == g_bloonFactory)
		{
			if (categoryId == 0)
			{
				result = g_bloonFlags.GetFlag(std::string(*textId));
			}
			if (categoryId == 1)
			{
				result = g_bloonStatusFlags.GetFlag(std::string(*textId));
			}
		}

		if (self == g_weaponFactory)
		{
			if (categoryId == 0)
			{
				result = g_weaponFlags.GetFlag(std::string(*textId));
			}
		}

		return result;
	}

	auto StringToFlag::Apply() -> bool
	{
		const void* address = Signatures::GetAddressOf(Sigs::CFlagStringConvertor_StringToFlag);
		if(address)
		{
			auto* detour = new PLH::x86Detour((const uint64_t)address, std::bit_cast<size_t>(&StringToFlag::cb_hook), &o_func);
			if(detour->hook())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
}