#pragma once

#include <string>

namespace NKHook5
{
	namespace Classes
	{
		class CTexture
		{
		public:
			char pad_0000[20]; //0x0000
			std::string texture_name; //0x0014
			std::string image_path; //0x002C
		};
	}
}