#include "IArchive.h"

using namespace NKHook5::Mod;
namespace fs = std::filesystem;

IArchive::IArchive(fs::path archivePath) {
	this->archivePath = archivePath;
}