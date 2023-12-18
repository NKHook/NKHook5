#include "Constructor.h"

#include "../../Classes/CTowerFactory.h"
#include "../../Signatures/Signature.h"

#include <Logging/Logger.h>

NKHook5::Classes::CTowerFactory* g_towerFactory = nullptr;

namespace NKHook5::Patches::CTowerFactory
{
	using namespace Signatures;
	using namespace Common;
	using namespace Common::Logging;
	using namespace Common::Logging::Logger;

	static uint64_t o_func;
	Classes::CTowerFactory* Constructor::cb_hook(void* param_1, void* param_2)
	{
		g_towerFactory = reinterpret_cast<Classes::CTowerFactory*>(this);
		Print(LogLevel::DEBUG, "g_towerFactory: %p", g_towerFactory);

		auto ofn = std::bit_cast<decltype(&Constructor::cb_hook)>(reinterpret_cast<void*>(o_func));
		return (this->*ofn)(param_1, param_2);
	}

	auto Constructor::Apply() -> bool
	{
		void* address = Signatures::GetAddressOf(Sigs::CTowerFactory_CCTOR);
		if(address)
		{
			auto* detour = new PLH::x86Detour((const uint64_t)address, std::bit_cast<size_t>(&Constructor::cb_hook), &o_func);
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