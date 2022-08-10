#include "NewFramework.h"

void* newframework_crt_malloc(size_t size) {
    //printf("Allocating %d bytes\n", size);
    return CdeclCall<void*, size_t>(NKHook5::Signatures::Sigs::CRT_operator_new, size);
}

void newframework_crt_free(void* ptr) {
    //printf("Freeing %p\n", ptr);
    return CdeclCall<void, void*>(NKHook5::Signatures::Sigs::CRT_free, ptr);
}

nfw::vtable_meta* nfw::vtable_get_meta_ptr(void* vtable) {
    return (nfw::vtable_meta*)(((char**)vtable)[-1]);
};