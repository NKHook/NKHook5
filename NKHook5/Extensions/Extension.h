#pragma once

#include <string>

/*
* Just to be clear on what extensions are:
* 
* Extensions are new additional features for the game's asset files. For example, this may be a new key, or new file alltogether.
*/

namespace NKHook5 {
	namespace Extensions {
		class Extension {
			std::string target;
		public:
			Extension(std::string target);
			virtual const std::string& GetTarget();
			virtual void UseData(void* content, size_t contentLen);
		};
	}
}