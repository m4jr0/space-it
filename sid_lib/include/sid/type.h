// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

// HEADER //////////////////////////////////////////////////////////////////////

#ifndef SID_LIB_TYPES_H_
#define SID_LIB_TYPES_H_

#include "compilers.h"

#ifdef SID_CPP
extern "C" {
#endif  // SID_CPP

#include <float.h>
#include <inttypes.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#include "os.h"

#define SID_CHAR_BIT CHAR_BIT

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef float f32;
typedef double f64;

typedef size_t uindex;
typedef uintptr_t uptr;
#define SID_UPTR_FORMAT PRIxPTR
typedef ptrdiff_t sptrdiff;

typedef char schar;
typedef unsigned char uchar;
typedef wchar_t wchar;

typedef s8 b8;
typedef s32 b32;

#define SID_TRUE true
#define SID_FALSE false
#define SID_NULL NULL

#ifdef SID_WINDOWS
typedef errno_t error_code;
#else
typedef s32 error_code;
#endif  // SID_WINDOWS

#define SID_U8_MIN 0
#define SID_U8_MAX UCHAR_MAX
#define SID_U16_MIN 0
#define SID_U16_MAX USHRT_MAX
#define SID_U32_MIN 0
#define SID_U32_MAX UINT_MAX
#define SID_U64_MIN 0
#define SID_U64_MAX ULONG_MAX
#define SID_S8_MIN SCHAR_MIN
#define SID_S8_MAX SCHAR_MAX
#define SID_S16_MIN SHRT_MIN
#define SID_S16_MAX SHRT_MAX
#define SID_S32_MIN INT_MIN
#define SID_S32_MAX INT_MAX
#define SID_S64_MIN LONG_MIN
#define SID_S64_MAX LONG_MAX
#define SID_UINDEX_MIN 0
#define SID_UINDEX_MAX UINT_MAX
#define SID_UPTR_MIN 0
#define SID_UPTR_MAX ULONG_MAX
#define SID_SPTRDIFF_MIN LONG_MIN
#define SID_SPTRDIFF_MAX LONG_MAX
#define SID_SCHAR_MIN SCHAR_MIN
#define SID_SCHAR_MAX SCHAR_MAX
#define SID_UCHAR_MIN 0
#define SID_UCHAR_MAX UCHAR_MAX
#define SID_WCHAR_MIN WCHAR_MIN
#define SID_WCHAR_MAX WCHAR_MAX
#define SID_F32_MIN FLT_MIN
#define SID_F32_MAX FLT_MAX
#define SID_F64_MIN DBL_MIN
#define SID_F64_MAX DBL_MAX
#define SID_B8_MIN CHAR_MIN
#define SID_B8_MAX CHAR_MAX
#define SID_B32_MIN INT_MIN
#define SID_B32_MAX INT_MAX

#ifdef SID_WIDE_TCHAR
typedef wchar tchar;
#define SID_TCHAR_MIN SID_SCHAR_MIN
#define SID_TCHAR_MAX SID_SCHAR_MAX

#define SID_TCHAR(str) L##str

#define SID_TCHAR_FORMAT "%ls"
#else
typedef schar tchar;
#define SID_TCHAR_MIN SID_WCHAR_MIN
#define SID_TCHAR_MAX SID_WCHAR_MAX

#define SID_TCHAR(str) str

#define SID_TCHAR_FORMAT "%s"
#endif  // SID_WIDE_TCHAR

#ifdef SID_64
typedef u64 ux;
typedef s64 sx;
typedef f64 fx;
#else
typedef u32 ux;
typedef s32 sx;
typedef f32 fx;
#endif  // SID_64

#define SID_INVALID_INDEX (uindex) - 1

#ifdef SID_CPP
}
#endif  // SID_CPP

#endif  // SID_LIB_TYPES_H_

////////////////////////////////////////////////////////////////////////////////