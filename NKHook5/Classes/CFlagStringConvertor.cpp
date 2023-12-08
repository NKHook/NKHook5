#include "CFlagStringConvertor.h"

using namespace NKHook5::Classes;
using namespace NKHook5::Signatures;

nfw::string CFlagStringConvertor::FlagToString(uint32_t category, uint64_t flag)
{
	return ThisCall<Sigs::CFlagStringConvertor_FlagToString>(&CFlagStringConvertor::FlagToString, this, category, flag);
}