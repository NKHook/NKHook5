#pragma once

/*
* Define at the beginning of any header or translation unit where allocation is necessary
* the game doesnt like when you don't use its allocators for some reason
*/

#include "../Classes/Macro.h"
#include "../Signatures/Signature.h"

void* newframework_crt_malloc(size_t size);
void newframework_crt_free(void* ptr);

#define malloc(size) newframework_crt_malloc(size);
#define free(ptr) newframework_crt_free(ptr);

#define GHSTL_MALLOC(size) malloc(size)
#define GHSTL_FREE(ptr) free(ptr)

#define overload_new \
    void* operator new(size_t size) { \
        return newframework_crt_malloc(size); \
    }