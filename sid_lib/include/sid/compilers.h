// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_COMPILERS_H_
#define SID_COMPILERS_H_

#ifdef __clang__
#define SID_CLANG
#elif defined(__GNUC__)
#define SID_GCC
#ifdef __GNUG__
#define SID_GCC_CPP
#else
#define SID_GCC_C
#endif  // __GNUG__
#elif defined(_MSC_VER)
#define SID_MSVC
#endif  // __clang__

#ifdef __cplusplus
#define SID_CPP
#else
#define SID_C
#endif  // __cplusplus

#ifdef SID_MSVC
#define SID_EXPORT __declspec(dllexport)
#else
#define SID_EXPORT __attribute__((visibility("default")))
#endif  // SID_MSVC

#endif  // SID_COMPILERS_H_