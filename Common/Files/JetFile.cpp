#include "JetFile.h"

using namespace Common;
using namespace Common::Files;
namespace fs = std::filesystem;

JetFile::JetFile() {

}

JetFile::JetFile(fs::path path) : ZipBase(path, JET_PASSWORD) {

}

bool JetFile::Open(std::filesystem::path path)
{
	ZipBase::Open(path);
	this->SetPassword(JET_PASSWORD);
	this->SetCompressionLevel(JET_COMPRESS_LEVEL);
	return true;
}
