#include "BmpPhoto.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_write.h>

using namespace Common;
using namespace Common::Files;
using namespace Common::Files::Images;
using namespace Common::Sprites;
using namespace Common::Sprites::Images;
namespace fs = std::filesystem;

BmpPhoto::BmpPhoto() : Photo() {
}

BmpPhoto::BmpPhoto(fs::path path) : Photo(path) {
}

bool BmpPhoto::Open(fs::path path) {
	return this->OpenRead(path);
}
bool BmpPhoto::OpenRead(fs::path path) {
	//Call the base Photo::OpenRead function
	Photo::OpenRead(path);

	//Variables for photo information
	int width = 0;
	int height = 0;
	int channels = 0;
	//Read the actual photo bytes
	uint32_t* colorBytes = (uint32_t*)stbi_load(path.string().c_str(), &width, &height, &channels, 4);
	//Store it all into a vector for simplicity
	std::vector<uint32_t> imgData;
	for (size_t i = 0; i < width * height; i++) {
		imgData.push_back(colorBytes[i]);
	}
	//Create a new MTImage with the image data on the GPU
	this->image = new MTImage(imgData, width, height);

	return true;
}
bool BmpPhoto::OpenWrite(fs::path path) {
	return Photo::OpenWrite(path);;
}

Images::MTImage* BmpPhoto::ReadImg() {
	return this->image;
}

void BmpPhoto::WriteImg(Images::MTImage* image) {
	//Call the base Photo::WriteImage function
	Photo::WriteImg(image);

	//Get the image width/height
	size_t width = image->GetWidth();
	size_t height = image->GetHeight();
	//Get the image colors vector
	std::vector<uint32_t> colors = image->ColorBytes();

	//Store the photo into a file
	stbi_write_bmp(this->GetPath().string().c_str(), width, height, 4, colors.data());
}