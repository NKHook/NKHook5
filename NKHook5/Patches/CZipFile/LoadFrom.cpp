#include "LoadFrom.h"

#include "../../Assets/AssetServer.h"

#include <Extensions/ExtensionManager.h>
#include <Files/File.h>
#include <Logging/Logger.h>

namespace NKHook5::Patches::CZipFile
{
	using namespace Common::Extensions;
	using namespace Common::Files;
	using namespace Common::Logging;
	using namespace Common::Logging::Logger;
	using namespace NKHook5;
	using namespace NKHook5::Signatures;
	using namespace NKHook5::Assets;

	uint64_t o_func;
	Classes::CUnzippedFile* LoadFrom::cb_hook(const nfw::string& assetPath, void* param_2, nfw::string& archivePassword) {
		//Get the extensions for the file
		std::vector<Extension*> extsForFile = ExtensionManager::GetByTarget(std::string(assetPath));

		Classes::CUnzippedFile* pAsset = nullptr;

		//Get the vanilla asset
		auto ofn = std::bit_cast<decltype(&LoadFrom::cb_hook)>(reinterpret_cast<void*>(o_func));
		pAsset = (this->*ofn)(assetPath, param_2, archivePassword);

		//Store the vanilla data into a vector
		std::vector<uint8_t> vanillaData;

		if (pAsset) {
			vanillaData = std::vector<uint8_t>(pAsset->fileSize);
			memcpy_s(vanillaData.data(), vanillaData.size(), pAsset->fileContent, pAsset->fileSize);
		}
		else {
			if (fs::exists(assetPath)) {
				File vanillaFile;
				vanillaFile.OpenRead(assetPath);
				vanillaData = vanillaFile.ReadBytes();
				vanillaFile.Close();
			}
			else {
#ifdef _DEBUG
				Print(LogLevel::ERR, "Failed to find asset: %s", assetPath.c_str());
#endif
			}
		}

		if (!vanillaData.empty()) {
			//Run extensions
			for (Extension* ext : extsForFile) {
				if (!ext->IsCustomDocument())
					ext->UseData(vanillaData.data(), vanillaData.size());
			}
		}

		//Get the AssetServer
		AssetServer* server = AssetServer::GetServer();
		//Serve the asset
		std::shared_ptr<Asset> servedAsset = server->Serve(assetPath, vanillaData);
		//If there is an asset to serve
		if (servedAsset != nullptr) {
			if (pAsset) {
				//Create a copy
				void* contentCopy = malloc(servedAsset->GetData().size());
				memcpy_s(
					contentCopy,
					servedAsset->GetData().size(),
					servedAsset->GetData().data(),
					servedAsset->GetData().size()
				);
				if (pAsset->fileContent) {
					free(pAsset->fileContent);
				}
				//Place the new pointer and size into the asset structure
				pAsset->fileContent = contentCopy;
				pAsset->fileSize = servedAsset->GetData().size();
			}
			else {
				pAsset = new Classes::CUnzippedFile(servedAsset);
			}
		}

		return pAsset;
	}

	auto LoadFrom::Apply() -> bool
	{
		const void* address = Signatures::GetAddressOf(Sigs::CZipFile_LoadFrom);
		if (address)
		{
			auto* detour = new PLH::x86Detour((const uint64_t)address, std::bit_cast<size_t>(&LoadFrom::cb_hook), &o_func);
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