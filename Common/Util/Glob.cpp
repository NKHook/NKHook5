#include "Glob.h"

using namespace Common;
using namespace Common::Util;
namespace fs = std::filesystem;

std::string Sanitize(std::string filePath) {
	while (filePath.find("\\") != std::string::npos) {
		size_t wrongSlashPos = filePath.find("\\");
		filePath[wrongSlashPos] = '/';
	}
	return filePath;
}

bool MatchPart(std::string pathPart, std::string globPart) {
	//If the glob part is just a wildcard, it will always patch
	if (globPart == "*") {
		return true;
	}

	//If there is a file extension, we want to make sure they match
	if (globPart.find(".") != std::string::npos && pathPart.find(".") != std::string::npos) {
		//Get the glob's stub
		std::string globStub = globPart.substr(0, globPart.find("."));
		//Get the glob's extension
		std::string globExt = globPart.substr(globPart.find(".")+1);

		//Get the path's stub
		std::string pathStub = pathPart.substr(0, pathPart.find("."));
		//Get the path's extension
		std::string pathExt = pathPart.substr(pathPart.find(".")+1);

		bool stubsMatch = MatchPart(pathStub, globStub);
		bool extensionsMatch = MatchPart(pathExt, globExt);

		return stubsMatch && extensionsMatch;
	}

	//In any other case, we just want to know if the strings match
	return pathPart == globPart;
}

Glob::Glob(std::string globStr) {
	//First we need to sanitize the path and replace all \\ with /
	std::string sanitizedGlob = Sanitize(globStr);

	//Split the globs parts
	while (sanitizedGlob.find("/") != std::string::npos) {
		size_t slashPos = sanitizedGlob.find("/");
		//Get the individual part
		std::string part = sanitizedGlob.substr(0, slashPos);
		//Append it to the vector
		this->globParts.push_back(part);
		//Next part
		sanitizedGlob = sanitizedGlob.substr(slashPos+1);
	}

	//Push the last part of the glob (stored in sanatizedGlob)
	if(!sanitizedGlob.empty())
		this->globParts.push_back(sanitizedGlob);
}

bool Glob::Match(std::string filePath) const {
	//First we need to sanitize the path and replace all \\ with /
	std::string sanitizedPath = Sanitize(filePath);

	std::vector<std::string> pathParts;
	//Split the globs parts
	while (sanitizedPath.find("/") != std::string::npos) {
		size_t slashPos = sanitizedPath.find("/");
		//Get the individual part
		std::string part = sanitizedPath.substr(0, slashPos);
		//Append it to the vector
		pathParts.push_back(part);
		//Next part
		sanitizedPath = sanitizedPath.substr(slashPos+1);
	}

	//Push the last part of the path (stored in sanatizedPath)
	if (!sanitizedPath.empty())
		pathParts.push_back(sanitizedPath);

	//If the parts are different sizes, they cant possibly match
	if (pathParts.size() != globParts.size()) {
		return false;
	}

	//Assume they match before checking
	bool theyMatch = true;

	//Match each part
	for (size_t i = 0; i < pathParts.size(); i++) {
		std::string pathPart = pathParts[i];
		std::string globPart = globParts[i];

		bool matches = MatchPart(pathPart, globPart);
		if (!matches) {
			theyMatch = false;
		}
	}

	return theyMatch;
}