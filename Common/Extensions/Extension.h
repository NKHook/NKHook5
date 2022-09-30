#pragma once

#include <string>

/*
* Just to be clear on what extensions are:
* 
* Extensions are new additional features for the game's asset files. For example, this may be a new key, or new file alltogether.
*/

namespace Common {
	namespace Extensions {
		class Extension {
			std::string name;
			std::string target;
		public:
			//Constructor
			Extension(std::string name, std::string target);
			virtual const std::string& GetName();
			virtual const std::string& GetTarget();
			//If the extension is its own file, or if it matches a vanilla file
			virtual bool IsCustomDocument();
			//When the data is received for the extension, this function will be called with the data
			virtual void UseData(void* content, size_t contentLen);
		};
	}
}