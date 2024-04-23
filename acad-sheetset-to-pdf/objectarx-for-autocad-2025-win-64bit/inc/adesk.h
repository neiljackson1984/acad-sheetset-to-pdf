//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2024 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
//
// DESCRIPTION:
//
// Note that C++ 11 (and VC11) now provide standard fixed size integer types
// such as int16_t, int32_t, etc, and those are now used here. Developers
// are encouraged to migrate over to using the standard C++ types.
//

#ifndef   _ADESK_H
#define   _ADESK_H

#if defined(__cplusplus)
#include <cstdint>             // int16_t, uint32_t, etc
#else
#include <stdint.h>
#endif
#include <stddef.h>             // size_t
#include "AdAChar.h"            // ACHAR typedef

// These conditions are always true and the macros are deprecated.  Please do not use.
#define Adesk_Boolean_is_bool 1
#define Adesk_Int32_is_int 1


#if defined(_MSC_VER)
#ifndef _ADESK_CROSS_PLATFORM_
    #define _ADESK_WINDOWS_ 1
#endif
#elif defined(__clang__)
#if defined(_ADESK_MAC_)
    #define __w64
#endif

#endif

#if (defined(_MSC_VER) && defined(_WIN64)) || (defined(__clang__) && defined(__LP64__))
#define _AC64 1
#endif

#if defined(__cplusplus)
struct Adesk
{
    // Some useful constants.  See also std::numeric_limits<> for min and max values
    //
    enum IntLiterals : long long {
       nMaxShort =      0x7fff,         // 32k-1 = 32,767
            n64K =    0x1'0000,         // 2**16 = 65,536
           n1Meg =   0x10'0000,         // 2**20 = 1,048,576
           n1Gig = 0x4000'0000,         // 2**30 = 1,073,741,824
          n1Tera =  0x100'0000'0000,    // 2**40 = 1,099,511,627,776
         nMaxInt = 0x7fff'ffff,         // 2G-1  = 2,147,483,647
        nMaxUInt = 0xffff'ffff};        // 4G-1  = 4,294,967,295

    // These Adesk types are all now redundant with native C++ types int8_t, uint32_t,
    // bool, etc.  Please use the native types in new code.

    //
    typedef int8_t      Int8;
    typedef int16_t     Int16;

    typedef uint8_t     UInt8;
    typedef uint16_t    UInt16;

    typedef int32_t     Int32;
    typedef uint32_t    UInt32;

    typedef int64_t     Int64;
    typedef uint64_t    UInt64;

    // Convenient abbreviations (use optionally).
    // Also obsolete and deprecated
    //
    typedef unsigned char  uchar;
    typedef unsigned short ushort;
    typedef unsigned int   uint;

    // integer/unsigned integers that can hold a pointer value.
    // These change size depending on the platform and should NEVER
    // be streamed out to permanent storage.
#if !defined(_WIN64) && !defined (_AC64)
    static_assert(sizeof(void *) == 4, "ptr size in 32-bit windows build?");
    typedef int32_t             LongPtr;
    typedef uint32_t            ULongPtr;
    typedef int32_t             IntPtr;
    typedef uint32_t            UIntPtr;
#else   // _WIN64 || _AC64

    static_assert(sizeof(void *) == 8, "ptr size in 64-bit build?");
    typedef int64_t             LongPtr;
    typedef uint64_t            ULongPtr;
    typedef int64_t             IntPtr;
    typedef uint64_t            UIntPtr;

#endif // _WIN64 || _AC64

    typedef LongPtr IntDbId;
    typedef IntPtr GsMarker;

    // Logical type (Note: never use int when Boolean is intended!)
    // Please transition from Boolean type to native bool..
    //
    typedef bool       Boolean;
    static constexpr bool kFalse = false;
    static constexpr bool kTrue = true;

    using Time64 = int64_t;

    //
    // four byte color representations
    //
    using ColorRef = uint32_t;  // 32-bit RGB value in Win32 COLORREF format 0x00bbggrr
    using RGBQuad  = uint32_t;  // 32-bit RGB value in Win32 RGBQUAD  format 0x00rrggbb
};
#endif // __cplusplus
// Deprecated.  Please transition from NULL macro to native nullptr..
#undef NULL
#define NULL 0

#ifdef _ADESK_MAC_
#ifdef nil
#undef nil
#endif
#define nil __DARWIN_NULL
#endif

// Use ADESK_NO_VTABLE on base classes which:
//   1. have virtual methods
//   2. are never instantiated
//   3. have a ctor and/or a dtor
//   4. do not call any virtual methods in the ctor or dtor
// This allows the compiler to avoid assigning a vtable pointer at
// the top of the base class's ctor and dtor.  So the vtable itself
// and any methods it points to which aren't used elsewhere can be
// omitted by the linker and reduce overall space.
//
// Make sure though that the base class is never instantiated.  Making
// the ctor protected or using pure virtual methods can help with this.
//
#if defined(_MSC_VER)
    #define ADESK_NO_VTABLE           __declspec(novtable)
    #define ADESK_STDCALL             __stdcall
    #define ADESK_DEPRECATED          __declspec(deprecated)
    #define ADESK_DEPRECATED_MSG(MSG) __declspec(deprecated(MSG))
    #define ADESK_DATA_IMPORT         __declspec(dllimport)
    #define ADESK_PACK_BEGIN __pragma(pack(push,1))
    #define ADESK_PACK_END __pragma(pack(pop))
    #define ADESK_HIDDEN_SYMBOL //symbols are hidden by default with MSVC toolchain
#else 
    #define ADESK_NO_VTABLE

    // The GCC 4.0 compiler doesn't seem to support the stdcall attribute
    // for 64-bit builds. If we use it, we just get a ton of warnings
    // from the compiler mentioning that it isn't supported.
    #if defined(__LP64__) || defined(__clang__)
        #define ADESK_STDCALL
    #else
        #define ADESK_STDCALL         __attribute__((stdcall))   
    #endif // __LP64__
    
    #define ADESK_DEPRECATED          __attribute__((__deprecated__))
    #define ADESK_DEPRECATED_MSG(MSG) __attribute__((__deprecated__))
    #define ADESK_DATA_IMPORT         extern

    // Redefine __declspec(method) for gcc
    #define __declspec(method) __declspec_##method
    #define _declspec(method) __declspec_##method

    #define __declspec_selectany      __attribute__ ((__weak__))

    #define __declspec_dllexport      __attribute__ ((__visibility__("default")))
    #define __declspec_dllimport      

    #define __declspec_noinline       __attribute__ ((__noinline__))
    #define __declspec_noreturn       __attribute__ ((__noreturn__))
    #define __declspec_deprecated     __attribute__ ((__deprecated__))
    #define __declspec_novtable
    #define __declspec_allocate(name) __attribute__ ((section("__DATA," name)))
    #define ADESK_PACK_BEGIN
    #define ADESK_PACK_END              __attribute__ ((packed))
    #define ADESK_HIDDEN_SYMBOL         __attribute__ ((visibility("hidden")))
#endif //_MSC_VER

#if defined(_MSC_EXTENSIONS) || defined (__clang__)
#define ADESK_OVERRIDE  override
    #if defined(_MSC_VER) && (_MSC_VER <= 1600) //VS2010 and earlier
        #define ADESK_SEALED sealed
    #else
#define ADESK_SEALED final
    #endif
#else //_MSC_EXTENSIONS
    #define ADESK_OVERRIDE
    #define ADESK_SEALED 
#endif //_MSC_EXTENSIONS

#define MIGRATION_ERRORS

#if defined(_MSC_VER) && defined (MIGRATION_ERRORS) || defined(__clang__)
    #define ADESK_SEALED_VIRTUAL virtual
    #if !defined(ADESK_SEALED)
        #define ADESK_SEALED sealed
    #endif //ADESK_SEALED
#else //MIGRATION_ERRORS
    #define ADESK_SEALED_VIRTUAL 
    #if !defined(ADESK_SEALED)
        #define ADESK_SEALED sealed
    #endif //ADESK_SEALED
#endif //MIGRATION_ERRORS

//
// Compiler indentification
//
#if defined(__INTEL_COMPILER) || defined (_MSC_VER)
    #define ADESK_FORCE_INLINE __forceinline
#else //__INTEL_COMPILER || _MSC_VER
    #define ADESK_FORCE_INLINE inline
#endif //__INTEL_COMPILER || _MSC_VER

#if defined(_ADESK_WINDOWS_) && !defined(__clang__)
#define VA_ARG_WCHAR(ap, t)      va_arg(ap, wchar_t)
#else
#define VA_ARG_WCHAR(ap, t)      va_arg(ap, int)
#endif

#ifdef _ADESK_UNITTEST_
#ifdef ADESK_SEALED
    #undef ADESK_SEALED
#endif
#define ADESK_SEALED
#endif

#ifdef _MSC_VER
#define ADESK_UNREFED_PARAM(x) x
#elif defined(__clang__)
#define ADESK_UNREFED_PARAM(x) (void)(x);
#else
#error Unknown compiler.
#endif

#ifdef _MSC_VER
#define ADESK_UNREACHABLE __assume(false)
#elif defined(__clang__)
#define ADESK_UNREACHABLE __builtin_unreachable()
#else
#error Unknown compiler.
#endif

#ifdef _MSC_VER
#define ADESK_FORCE_OPTNONE
#elif defined(__clang__)
    #if defined(__apple_build_version__) && ((__clang_major__ > 8) || ((__clang_major__ == 8) && (__clang_minor__ >= 1)))
        #define ADESK_APPLE_WITH_CLANG_8_1_OR_HIGHER
    #endif
    /** 
     * Mac, iOS and Android are facing unexpected behavior in certain functions when clang optimization is turned on. For example: on Android,
     * viewport clipping issues occured unless clang optimization was turned off. See https://jira.autodesk.com/browse/ACD-4516
     * On iOS and Mac this issue was confirmed on clang 8.1 and on Android on clang version 8.0.
     **/
    #if defined(__ANDROID__) || defined(ADESK_APPLE_WITH_CLANG_8_1_OR_HIGHER)
        #define ADESK_FORCE_OPTNONE __attribute__((optnone))
    #else
        #define ADESK_FORCE_OPTNONE
    #endif
#else
    #error Unknown compiler.
#endif

// Emscripten uses EMSCRIPTEN_KEEPALIVE to export symbols rather than
// __declspec(dllexport). Define ADESK_EXPORT to use the relevant
// export macro based on the current platform.
#if defined(_ADESK_WEB_)
    /*
    NOTE: We are disabling exporting functions using this macro in case of WEB.
    Minimum required number of functions are exported using exports.json
    This is done to:
    1. keep the wasm size small for the time being, until needed
    2. web xe2e tests for debug otherwise runs slow and starts failing due to timeout
    */
    // #include <emscripten.h>
    // #define ADESK_EXPORT EMSCRIPTEN_KEEPALIVE
    #define ADESK_EXPORT 
#else
    #define ADESK_EXPORT __declspec(dllexport)
#endif

// The [[nodiscard]] attribute is not available in
// all of our components.
// The ADESK_NODISCARD macro is a convenience to check
// if the nodiscard feature is present, and then conditionally
// compile it into the translation unit if it is.
#ifdef __has_cpp_attribute
    #if __has_cpp_attribute(nodiscard)
        #define ADESK_NODISCARD [[nodiscard]]
    #endif
#endif
#ifndef ADESK_NODISCARD
    #define ADESK_NODISCARD
#endif


#ifdef _ADESK_CROSS_PLATFORM_
// This macro will deprecate some APIs for Autodesk internal code.  These APIs will likely have an alternative version
// that is more suitable for internal use.
#define ADESK_DEPRECATE_FOR_INTERNAL_USE ADESK_DEPRECATED
#else
#define ADESK_DEPRECATE_FOR_INTERNAL_USE
#endif

// Suppresses the deprecated API warning for the next line
#define ADESK_SUPPRESS_DEPRECATED _Pragma("warning(suppress:4996)")


#endif //_ADESK_H
