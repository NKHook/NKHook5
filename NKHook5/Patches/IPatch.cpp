#include "IPatch.h"

using namespace NKHook5::Patches;

IPatch::IPatch(std::string name)
{
    this->name = name;
}
auto IPatch::GetName() -> std::string
{
    return this->name;
}
auto IPatch::GetDis() -> PLH::ZydisDisassembler&
{
    return *dis;
}
auto IPatch::Apply() -> bool
{
    return false;
}