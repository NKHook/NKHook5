#pragma once
#include <string>
#include "CTextureLoader.h"

using namespace std;
void* GetSpriteInfoPtr(CTextureLoader* ctl, string* spriteSheet, string* spriteName);
void* __fastcall LoadCompound(CTextureLoader* ctl, string* path, string* fileName);