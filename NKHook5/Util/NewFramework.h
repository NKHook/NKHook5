#pragma once

/*
* Define at the beginning of any header or translation unit where allocation is necessary
* the game doesnt like when you don't use its allocators for some reason
*/

#include "../Classes/Macro.h"
#include "../Signatures/Signature.h"
#include <list>
#include <map>

void* newframework_crt_malloc(size_t size);
void newframework_crt_free(void* ptr);

#define malloc(size) newframework_crt_malloc(size)
#define free(ptr) newframework_crt_free(ptr)

#define GHSTL_MALLOC(size) malloc(size)
#define GHSTL_FREE(ptr) free(ptr)

#define overload_new \
    void* operator new(size_t size) { \
        return newframework_crt_malloc(size); \
    };

namespace nfw {
    class class_descriptor
    {
    public:
        int32_t signature; //0x0000
        int32_t attributes; //0x0004
        int32_t N00001A93; //0x0008
        void** pBaseClassArray; //0x000C
    }; //Size: 0x0010

    class type_descriptor
    {
    public:
        void* type_info_vtable; //0x0000
        char pad_0004[4]; //0x0004
        const char name; //0x0008
    }; //Size: 0x000C

    class vtable_meta
    {
    public:
        int32_t signature; //0x0000
        int32_t offset; //0x0004
        int32_t cdOffset; //0x0008
        class type_descriptor* pTypeDescriptor; //0x000C
        class class_descriptor* pClassDescriptor; //0x0010
    }; //Size: 0x0014

    vtable_meta* vtable_get_meta_ptr(void* vtable);

    void* class_get_vtable_ptr(void* object);

    std::string typeof(void* object);

    template <class T>
    class newframework_allocator
    {
    public:
        typedef size_t    size_type;
        typedef ptrdiff_t difference_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef T         value_type;

        newframework_allocator() {}
        newframework_allocator(const newframework_allocator&) {}

        pointer allocate(size_type n, const void* = 0) {
            return (T*)newframework_crt_malloc(n * sizeof(T));
        }

        void deallocate(void* p, size_type) {
            if (p) {
                newframework_crt_free(p);
            }
        }

        pointer address(reference x) const { return &x; }
        const_pointer address(const_reference x) const { return &x; }
        newframework_allocator<T>& operator=(const newframework_allocator&) { return *this; }
        void construct(pointer p, const T& val)
        {
            new ((T*)p) T(val);
        }
        void destroy(pointer p) { p->~T(); }

        size_type max_size() const { return size_t(-1); }

        template <class U>
        struct rebind { typedef newframework_allocator<U> other; };

        template <class U>
        newframework_allocator(const newframework_allocator<U>&) {}

        template <class U>
        newframework_allocator& operator=(const newframework_allocator<U>&) { return *this; }
    };

    template<typename K, typename V>
    using map = std::map<K, V, std::less<K>, newframework_allocator<std::pair<const K, V>>>;

    template<typename T>
    using list = std::list<T, newframework_allocator<T>>;
}