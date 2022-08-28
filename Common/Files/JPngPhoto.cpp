#include "JPngPhoto.h"

using namespace Common;
using namespace Common::Files;

JPngPhoto::JPngPhoto()
{
}

JPngPhoto::JPngPhoto(std::filesystem::path path)
{
}

bool JPngPhoto::Open(std::filesystem::path)
{
	return false;
}

bool JPngPhoto::OpenRead(std::filesystem::path)
{
	return false;
}

bool JPngPhoto::OpenWrite(std::filesystem::path)
{
	return false;
}

Image* JPngPhoto::ReadImg()
{
	return nullptr;
}

void JPngPhoto::WriteImg(Image*)
{
}
