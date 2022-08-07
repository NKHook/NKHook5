#include "ZipBase.h"

using namespace Common;
using namespace Common::Files;
namespace fs = std::filesystem;

ZipBase::ZipBase() : IFile() {
	this->compressionLevel = 0;
}

ZipBase::ZipBase(fs::path path, std::string password) : IFile(path, 0)
{
	this->password = password;
}

bool ZipBase::Open(std::filesystem::path path)
{
	this->archive = ZipFile::Open(path.string());
	return this->archive != nullptr;
}

void ZipBase::Close() {
	ZipArchive* pArch = this->archive.get();
	this->archive.reset();
}

size_t ZipBase::GetSize()
{
	return this->archive->GetEntriesCount();
}

void ZipBase::SetPassword(std::string password)
{
	this->password = password;
}

void ZipBase::SetCompressionLevel(size_t level)
{
	this->compressionLevel = level;
}

std::vector<std::string> const ZipBase::GetEntries() const
{
	std::vector<std::string> result;
	for (size_t i = 0; i < this->archive->GetEntriesCount(); i++) {
		auto entry = this->archive->GetEntry(i);
		result.push_back(entry->GetFullName());
	}
	return result;
}