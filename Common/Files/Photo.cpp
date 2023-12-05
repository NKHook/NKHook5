#include "Photo.h"

#include <Logging/Logger.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

using namespace Common;
using namespace Common::Files;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;
using namespace Common::Logging::Logger;
namespace fs = std::filesystem;

Photo::Photo() : File() {
	this->writeMode = false;
}

Photo::Photo(fs::path path) : File() {
	this->writeMode = false;
	if (!this->Open(path)) {
		Print(LogLevel::ERR, "Failed to open photo %s", path.string().c_str());
	}
}

bool Photo::Open(fs::path path) {
	IFile::Open(path);
	return this->OpenRead(path);
};
bool Photo::OpenRead(fs::path path) {
	IFile::Open(path);
	this->writeMode = false;
	return true;
};
bool Photo::OpenWrite(fs::path path) {
	IFile::Open(path);
	this->writeMode = true;
	return true;
};

MTImage* Photo::ReadImg() {
	return nullptr;
}

void Photo::WriteImg(MTImage* image) {
}