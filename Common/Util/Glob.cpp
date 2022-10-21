#include "Glob.h"

using namespace Common;
using namespace Common::Util;
namespace fs = std::filesystem;

Glob::Glob(std::string globStr) {
	//First we need to sanitize the path and replace all \\ with /
	while (globStr.find("\\") != std::string::npos) {
		size_t wrongSlashPos = globStr.find("\\");
		globStr[wrongSlashPos] = '/';
	}

	//Split the globs parts
	while (globStr.find("/") != std::string::npos) {
		size_t slashPos = globStr.find("/");
		//Get the individual part
		std::string part = globStr.substr(0, slashPos);
		//Append it to the vector
		this->globParts.push_back(part);
		//Next part
		globStr = globStr.substr(slashPos);
	}
}

bool Glob::Match(fs::path filePath) {
	
}