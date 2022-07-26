#include "Extension.h"

using namespace NKHook5::Extensions;

Extension::Extension(std::string target) {
	this->target = target;
}

const std::string& Extension::GetTarget()
{
	return this->target;
}

bool NKHook5::Extensions::Extension::IsCustomDocument()
{
	return false;
}

void Extension::UseData(void* content, size_t contentLen)
{

}
