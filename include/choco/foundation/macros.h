//
// Created by jakit on 2023/6/18.
//

#ifndef CHOCO_MACROS_H
#define CHOCO_MACROS_H

#ifdef  __cplusplus
#define CHOCO_BEGIN_DECLS  extern "C" {
#define CHOCO_END_DECLS    }
#else
#define CHOCO_BEGIN_DECLS
#define CHOCO_END_DECLS
#endif

#define CHOCO_NO 0
#define CHOCO_YES 1

namespace Choco {
    typedef char Int8;
    typedef unsigned char UInt8;
    typedef short Int16;
    typedef unsigned short UInt16;
    typedef int Int32;
    typedef unsigned int UInt32;
    typedef long long Int64;
    typedef unsigned long long UInt64;
    typedef UInt8 Byte;
    typedef Int64 Integer;
    typedef UInt64 UInteger;
    typedef UInt64 Size;
    typedef Int64 SSize;

#if _WIN64
    typedef unsigned long long Pointer;
#elif _WIN32
    typedef unsigned int Pointer;
#else
typedef unsigned long long Pointer;
#endif
}

#ifdef _WIN32
#define CHOCO_API __declspec(dllexport)
#define CHOCO_DECL __cdecl
#else
#define CHOCO_API __attribute__((visibility("default")))
#define CHOCO_DECL __cdecl
#endif

#ifdef NDEBUG
#define CHOCO_ASSERT(condition) ((void) 0)
#define CHOCO_STATIC_ASSERT(condition, ...) ((void) 0)
#else
#define CHOCO_ASSERT(condition) assert(condition)
#define CHOCO_STATIC_ASSERT(condition, ...) static_assert(condition, "" # __VA_ARGS__)
#endif

#define CHOCO_ENUM(_type, _name) _type _name; enum

#endif //CHOCO_MACROS_H
