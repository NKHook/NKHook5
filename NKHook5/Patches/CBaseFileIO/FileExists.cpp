#include "FileExists.h"

#include <Logging/Logger.h>

#include "../../Assets/Asset.h"
#include "../../Assets/AssetServer.h"
#include "../../Classes/CUnzippedFile.h"
#include "../../Classes/CZipFile.h"

#include <string>

namespace NKHook5::Patches::CBaseFileIO
{
	using namespace Common;
	using namespace Common::Logging;
	using namespace Common::Logging::Logger;
	using namespace NKHook5;
	using namespace NKHook5::Assets;
	using namespace NKHook5::Signatures;

	static uint64_t o_func;
	static Classes::CZipFile* assetsArchive;
	bool FileExists::cb_hook(const nfw::string& assetPath, int policy) {
		bool result = false;

		//Get the AssetServer
		AssetServer* server = AssetServer::GetServer();
		//Check if an asset exists
		result = server->Has(assetPath);

		//If we cannot find the file
		if (!result) {
			//Let the game try
			auto ofn = std::bit_cast<decltype(&FileExists::cb_hook)>(reinterpret_cast<void*>(o_func));
			result = (this->*ofn)(assetPath, policy);
		}

#ifdef _DEBUG
		Print("Found %x: %s", result, assetPath.c_str());
#endif

		return result;
	}

	auto FileExists::Apply() -> bool
	{
		const void* address = Signatures::GetAddressOf(Sigs::CBaseFileIO_FileExists);
		if (address)
		{
			auto* detour = new PLH::x86Detour((const uint64_t)address, std::bit_cast<size_t>(&FileExists::cb_hook), &o_func);
			if (detour->hook())
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