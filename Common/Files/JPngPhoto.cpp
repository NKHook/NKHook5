#include "JPngPhoto.h"

#include <stb_image.h>

using namespace Common;
using namespace Common::Files;

constexpr int JPNG_JFIF_PTR = 0x1C;
constexpr int JPNG_PNG_PTR = 0x10;

static std::mutex openmtx;

JPngPhoto::JPngPhoto()
{
}

JPngPhoto::JPngPhoto(std::filesystem::path path)
{
}

bool JPngPhoto::Open(std::filesystem::path path)
{
	IFile::Open(path);
	return this->OpenRead(path);
}

bool JPngPhoto::OpenRead(std::filesystem::path path)
{
	std::lock_guard<std::mutex> lock(openmtx);
	File::OpenRead(path);
	std::ifstream imageStream;
	imageStream.open(this->GetPath(), std::ios::in | std::ios::binary);
	if (!imageStream.is_open())
		return false;
	std::vector<uint8_t> imageBytes((std::istreambuf_iterator<char>(imageStream)), std::istreambuf_iterator<char>());
	uint8_t* imageRaw = imageBytes.data();
	if (memcmp(imageRaw, "\x89\x50\x4E\x47", 4) == 0)
	{
		printf("Tried to read a JPNG image from a PNG file!\n");
		return false;
	}
	uint32_t imageSize = imageBytes.size();

	//The jpeg is the start, so just point to the beginning
	uint32_t* jfifOffset = (uint32_t*)(((size_t)imageRaw) + imageSize - JPNG_JFIF_PTR);
	uint8_t* jfifData = (uint8_t*)(((size_t)imageRaw) + *jfifOffset);

	//The PNG data pointer is at offset -0x10
	uint32_t* pngOffset = (uint32_t*)(((size_t)imageRaw) + imageSize - JPNG_PNG_PTR);
	uint8_t* pngData = (uint8_t*)(((size_t)imageRaw) + *pngOffset);

	uint32_t jfifSize = *pngOffset;
	uint32_t pngSize = (imageSize - *pngOffset) - JPNG_PNG_PTR;

	//Reconstruct vectors to make my life easier (vector of file bytes, not colors)
	std::vector<uint8_t> jfifVec(jfifData, jfifData + jfifSize);
	std::vector<uint8_t> pngVec(pngData,pngData + pngSize);

	int jfifWidth = 0;
	int jfifHeight = 0;
	int jfifChannels = 0;
	uint32_t* jfifColors = (uint32_t*)stbi_load_from_memory(jfifVec.data(), jfifVec.size(), &jfifWidth, &jfifHeight, &jfifChannels, STBI_rgb_alpha);
	std::vector<uint32_t> jfifColorVec(jfifColors, jfifColors + (jfifWidth * jfifHeight));

	int pngWidth = 0;
	int pngHeight = 0;
	int pngChannels = 0;
	uint32_t* pngColors = (uint32_t*)stbi_load_from_memory(pngVec.data(), pngVec.size(), &pngWidth, &pngHeight, &pngChannels, STBI_rgb_alpha);
	std::vector<uint32_t> pngColorVec(pngColors, pngColors + (pngWidth * pngHeight));

	if (jfifWidth != pngWidth)
	{
		throw std::exception("jfifWidth and pngWidth DO NOT MATCH!");
	}
	if (jfifHeight != pngHeight)
	{
		throw std::exception("jfifWidth and pngWidth DO NOT MATCH!");
	}

	std::vector<uint32_t> jpngColors;
	for (size_t i = 0; i < jfifColorVec.size(); i++)
	{
		uint32_t color = jfifColorVec[i];
		((uint8_t*)&color)[3] = ((uint8_t*)&(pngColorVec[i]))[0];
		jpngColors.push_back(color);
	}

	this->jpngImage = new CLImage(jpngColors, jfifWidth, jfifHeight);

	/*CLImage* jpegImage = new CLImage(jfifColorVec, jfifWidth, jfifHeight);
	CLImage* pngImage = new CLImage(pngColorVec, pngWidth, pngHeight);

	this->jpngImage = jpegImage->CopyImage();
	this->jpngImage->PasteChannel(pngImage, 1);*/

	stbi_image_free(jfifColors);
	stbi_image_free(pngColors);
	/*delete jpegImage;
	delete pngImage;*/

	return true;
}

bool JPngPhoto::OpenWrite(std::filesystem::path)
{
	std::lock_guard<std::mutex> lock(openmtx);
	return false;
}

Image* JPngPhoto::ReadImg()
{
	return this->jpngImage;
}

void JPngPhoto::WriteImg(Image*)
{
}
