#include "SpriteCell.h"

using namespace Common;
using namespace Common::Sprites;

SpriteCell::SpriteCell(std::string name, size_t x, size_t y, size_t w, size_t h, size_t ax, size_t ay, size_t aw, size_t ah)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->ax = ax;
	this->ay = ay;
	this->aw = aw;
	this->ah = ah;
}