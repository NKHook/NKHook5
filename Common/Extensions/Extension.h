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
			Extension(std::string name, std::string target);
			virtual const std::string& GetName();
			virtual const std::string& GetTarget();
			virtual bool IsCustomDocument();
			virtual void UseData(void* content, size_t contentLen);
		};
	}
}