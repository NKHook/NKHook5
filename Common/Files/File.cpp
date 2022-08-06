#include "File.h"

using namespace Common::Files;
namespace fs = std::filesystem;

File::File(fs::path path)
{
	this->path = path;
}

const fs::path& File::GetPath()
{
	return this->path;
}

size_t File::GetSize()
{
	std::ifstream in(this->path, std::ifstream::ate | std::ifstream::binary);
	size_t size = in.tellg();
	in.close();
	return size;
}

std::string File::ReadStr()
{
	std::vector<char> read = this->Read<char>();
	return std::string(read.data(), read.size() * sizeof(char));
}

void File::WriteStr(std::string data)
{
	std::vector<char> write(data.begin(), data.end());
	this->Write(write);
}
