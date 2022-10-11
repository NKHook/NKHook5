#include "AssetServer.h"

#include <Logging/Logger.h>
#include <Util/Json/MergedDocument.h>

using namespace Common;
using namespace Common::Logging;
using namespace Common::Logging::Logger;
using namespace Common::Util::Json;
using namespace NKHook5;
using namespace NKHook5::Assets;
namespace fs = std::filesystem;

static AssetServer* server = nullptr;

AssetServer* AssetServer::GetServer() {
	if (server == nullptr) {
		server = new AssetServer();
	}
	return server;
}

void AssetServer::AddSource(AssetSource* source) {
	this->sources.push_back(source);
}

std::shared_ptr<Asset> AssetServer::Serve(fs::path assetPath) {
	AssetBin theBin = FromPath(assetPath);

	if (theBin == AssetBin::JSON) {
		return this->ServeJSON(assetPath);
	}

	if (assetPath.filename().string().ends_with(".xml")) {
		return this->ServeXML(assetPath);
	}
}

std::shared_ptr<Asset> AssetServer::ServeGeneric(fs::path assetPath) {
	std::vector<std::shared_ptr<Asset>> finds;
	for (AssetSource* source : this->sources) {
		std::shared_ptr<Asset> find = source->Find(assetPath);
		if (find != nullptr) {
			finds.push_back(find);
		}
	}

	return finds[0];
}

std::shared_ptr<Asset> AssetServer::ServeJSON(fs::path assetPath) {
	std::vector<std::shared_ptr<Asset>> finds;
	for (AssetSource* source : this->sources) {
		std::shared_ptr<Asset> find = source->Find(assetPath);
		if (find != nullptr) {
			finds.push_back(find);
		}
	}

	try {
		MergedDocument merged;

	}
	catch (std::exception& ex) {
		Print("Error whilst merging JSON documents: %s", ex.what());
		return nullptr;
	}
}