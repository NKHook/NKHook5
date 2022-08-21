#include "Photo.h"

using namespace Common;
using namespace Common::Files;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;
namespace fs = std::filesystem;

Photo::Photo() : File() {
	this->image = nullptr;
	this->writeMode = false;
}

Photo::Photo(fs::path path) : File() {
	this->image = nullptr;
	this->writeMode = false;
	if (!this->Open(path)) {
		printf("Failed to open photo %s\n", path.string().c_str());
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

Image* Photo::ReadImg() {
	return this->image;
}

void Photo::WriteImg(Image* image) {
	if (this->image != nullptr) {
		delete this->image;
	}
	this->image = image;
}