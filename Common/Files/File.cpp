#include "File.h"

using namespace Common::Files;
namespace fs = std::filesystem;

File::File() {
	this->writeMode = false;
}

File::File(fs::path path) : IFile(path, 0)
{
	if (!this->Open(path)) {
		printf("Failed to open file %s\n", path.string().c_str());
	}
}

bool File::Open(fs::path path)
{
	IFile::Open(path);
	return this->OpenRead(path);
}

bool File::OpenRead(std::filesystem::path path)
{
	IFile::Open(path);
	if(this->stream.is_open())
		this->Close();
	this->writeMode = false;
	this->stream.open(this->GetPath(), std::ios::in | std::ios::binary);
	return this->stream.is_open();
}

bool File::OpenWrite(std::filesystem::path path)
{
	IFile::Open(path);
	if (this->stream.is_open())
		this->Close();
	this->writeMode = true;
	this->stream.open(this->GetPath(), std::ios::out | std::ios::binary);
	return this->stream.is_open();
}

File::~File() {
	this->Close();
}

void File::Close()
{
	this->stream.close();
}

size_t File::GetSize()
{
	return fs::file_size(this->GetPath());
}

std::vector<uint8_t> File::ReadBytes()
{
	if (this->stream.is_open()) {
		this->Close();
	}
	this->OpenRead(this->GetPath());
	std::vector<uint8_t> result((std::istreambuf_iterator<char>(this->stream)), std::istreambuf_iterator<char>());
	return result;
}

void File::WriteBytes(std::vector<uint8_t> data)
{
	if (this->stream.is_open()) {
		this->Close();
	}
	this->OpenWrite(this->GetPath());
	this->stream.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
}

std::string File::ReadStr()
{
	std::vector<uint8_t> read = this->ReadBytes();
	return std::string((const char*)read.data(), read.size() * sizeof(char));
}

void File::WriteStr(std::string data)
{
	std::vector<uint8_t> write(data.begin(), data.end());
	this->WriteBytes(write);
}
