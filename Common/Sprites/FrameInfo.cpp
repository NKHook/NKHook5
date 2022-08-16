#include "FrameInfo.h"

using namespace Common::Sprites;

FrameInfo::FrameInfo(std::string name, TexType type, size_t texw, size_t texh) : TexInfo(name, type) {
	this->texw = texw;
	this->texh = texh;
}