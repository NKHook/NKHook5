#include "IFile.h"

#include <Logging/Logger.h>

using namespace Common;
using namespace Common::Files;
using namespace Common::Logging::Logger;
namespace fs = std::filesystem;

Common::Files::IFile::IFile()
{
	this->size = 0;
}

IFile::IFile(std::filesystem::path path, size_t size)
{
	if (!this->Open(path)) {
		Print(LogLevel::ERR, "Failed to open IFile: %s", path.string().c_str());
		return;
	}
	this->size = size;
}

bool IFile::Open(std::filesystem::path path)
{
	this->path = path;
	return true;
}

void IFile::Close() {}

const fs::path& IFile::GetPath() const
{
	return this->path;
}

size_t IFile::GetSize() const
{
	return this->size;
}

std::vector<uint8_t> IFile::ReadBytes()
{
	return std::vector<uint8_t>();
}

void IFile::WriteBytes(std::vector<uint8_t> data)
{
	return;
}
