#include "NewFramework.h"

void* newframework_crt_malloc(size_t size) {
    //printf("Allocating %d bytes\n", size);
    return CdeclCall<NKHook5::Signatures::Sigs::CRT_operator_new, void*>(size);
}

void newframework_crt_free(void* ptr) {
    //printf("Freeing %p\n", ptr);
    return CdeclCall<NKHook5::Signatures::Sigs::CRT_free, void>(ptr);
}

nfw::vtable_meta* nfw::vtable_get_meta_ptr(void* vtable) {
    return (nfw::vtable_meta*)(((char**)vtable)[-1]);
}

void* nfw::class_get_vtable_ptr(void* object) {
    return *(void**)object;
}

std::string nfw::typeof(void* object)
{
    void* vtable_ptr = nfw::class_get_vtable_ptr(object);
    nfw::vtable_meta* meta_ptr = nfw::vtable_get_meta_ptr(vtable_ptr);
    nfw::type_descriptor* type_info = meta_ptr->pTypeDescriptor;
    const char* type_name = &type_info->name;
    std::string typeName = type_name;
    return typeName;
}

__declspec(naked) void* __cdecl nfw::mftp(...)
{
    __asm
    {
        mov eax, [esp+4]
        ret
    }
}