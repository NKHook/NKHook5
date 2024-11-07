#include "PngPhoto.h"

#include <stb_image.h>
#include <stb_image_write.h>

#include <mutex>

using namespace Common;
using namespace Common::Files;
using namespace Common::Files::Images;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;
namespace fs = std::filesystem;

static std::mutex openmtx;

PngPhoto::PngPhoto() : Photo() {
}

PngPhoto::PngPhoto(fs::path path) : Photo(path) {
}

bool PngPhoto::Open(fs::path path) {
	return this->OpenRead(path);
}
bool PngPhoto::OpenRead(fs::path path) {
	std::lock_guard<std::mutex> lock(openmtx);
	Photo::OpenRead(path);

	int width = 0;
	int height = 0;
	int channels = 0;
	uint32_t* colorBytes = (uint32_t*)stbi_load(path.string().c_str(), &width, &height, &channels, 4);
	std::vector<uint32_t> imgData(colorBytes, colorBytes + (width * height));

	this->image = new MTImage(imgData, width, height);

	return true;
}
bool PngPhoto::OpenWrite(fs::path path) {
	std::lock_guard<std::mutex> lock(openmtx);
	return Photo::OpenWrite(path);;
}

Images::MTImage* PngPhoto::ReadImg() {
	return this->image;
}

void PngPhoto::WriteImg(Images::MTImage* image) {
	std::lock_guard<std::mutex> lock(openmtx);
	Photo::WriteImg(image);

	size_t width = image->GetWidth();
	size_t height = image->GetHeight();
	const std::vector<uint32_t>& colors = image->ColorBytes();

	stbi_write_png(this->GetPath().string().c_str(), width, height, 4, colors.data(), width * 4);
}