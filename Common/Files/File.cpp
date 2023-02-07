#include "File.h"

#include <Logging/Logger.h>

using namespace Common::Files;
using namespace Common::Logging::Logger;
namespace fs = std::filesystem;

File::File() {
	this->writeMode = false;
}

File::File(fs::path path) : IFile(path, 0)
{
	if (!this->Open(path)) {
		Print(LogLevel::ERR, "Failed to open file %s", path.string().c_str());
	}
}

bool File::Open(fs::path path)
{
	IFile::Open(path);
	return this->OpenRead(path);
}

bool File::OpenRead(std::filesystem::path path)
{
	//Call the interface IFile::Open function
	IFile::Open(path);
	//Check if the stream is already open
	if(this->stream.is_open())
		//Close it, we need to reopen it with a different mode
		this->Close();
	//Set writeMode to false
	this->writeMode = false;
	//Open the stream (again)
	this->stream.open(this->GetPath(), std::ios::in | std::ios::binary);
	//Returns true if it was successfully opened
	return this->stream.is_open();
}

bool File::OpenWrite(std::filesystem::path path)
{
	//Call the base IFile::Open
	IFile::Open(path);
	//Check if the stream is open
	if (this->stream.is_open())
		//If so, close it to change the mode
		this->Close();
	//Set writeMode to true
	this->writeMode = true;
	//Open the stream in write mode
	this->stream.open(this->GetPath(), std::ios::out | std::ios::binary);
	//Returns true if it was successfully opened
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
	//Call the OpenRead function to open the file in read mode
	this->OpenRead(this->GetPath());
	//Get the result from the file stream & store it in a vector
	std::vector<uint8_t> result((std::istreambuf_iterator<char>(this->stream)), std::istreambuf_iterator<char>());
	//Return the vector
	return result;
}

void File::WriteBytes(std::vector<uint8_t> data)
{
	if (this->stream.is_open()) {
		this->Close();
	}
	//Open the file in write mode
	this->OpenWrite(this->GetPath());
	//Write the entire data vector to the file
	this->stream.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(uint8_t));
}

std::string File::ReadStr()
{
	//Read the bytes for the file
	std::vector<uint8_t> read = this->ReadBytes();
	//Convert to a string and return
	return std::string((const char*)read.data(), read.size() * sizeof(char));
}

void File::WriteStr(std::string data)
{
	//Convert the string to save into a vector
	std::vector<uint8_t> write(data.begin(), data.end());
	//Write the vector bytes
	this->WriteBytes(write);
}
