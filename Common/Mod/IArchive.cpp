#include "IArchive.h"

using namespace Common::Mod;
namespace fs = std::filesystem;

IArchive::IArchive(fs::path archivePath) {
	this->archivePath = archivePath;
}