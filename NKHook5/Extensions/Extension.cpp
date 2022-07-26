#include "Extension.h"

using namespace NKHook5::Extensions;

Extension::Extension(std::string target) {
	this->target = target;
}

const std::string& Extension::GetTarget()
{
	return this->target;
}

void Extension::UseData(void* content, size_t contentLen)
{

}
