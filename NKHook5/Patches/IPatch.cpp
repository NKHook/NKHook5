#include "IPatch.h"
#include <Windows.h>

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
void IPatch::WriteBytes(uintptr_t address, const char* bytes, size_t len)
{
    unsigned long oldProt;
    VirtualProtect((void*)address, len, PAGE_EXECUTE_READWRITE, &oldProt);
    memcpy_s((void*)address, len, bytes, len);
    VirtualProtect((void*)address, len, oldProt, &oldProt);
}
auto IPatch::Apply() -> bool
{
    return false;
}