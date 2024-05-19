// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_LIB_OS_H_
#define SID_LIB_OS_H_

#ifdef _WIN32
#define SID_WINDOWS
#endif  // _WIN32

#ifdef __linux__
#define SID_LINUX
#endif  // __linux__

#ifdef __APPLE__
#define SID_APPLE
#endif  // __APPLE__

#if defined __linux__ || defined __APPLE__ || defined __sun || \
    defined __FreeBSD__ || defined __NetBSD__ || defined __OpenBSD__
#define SID_UNIX
#endif  // __linux__ || defined __APPLE__ || defined __sun || __FreeBSD__ ||
        // defined __NetBSD__ || defined __OpenBSD__

#ifdef SID_WINDOWS
#ifdef _WIN64
#define SID_64
#else
#define SID_32
#endif  // _WIN64
#endif  // SID_WINDOWS

// Check GCC
#if defined SID_UNIX || defined SID_APPLE
#if __x86_64__ || __ppc64__
#define SID_64
#else
#define SID_32
#endif
#endif  // defined SID_UNIX || defined SID_APPLE

#define SID_EXIT_SUCCESS EXIT_SUCCESS
#define SID_EXIT_FAILURE EXIT_FAILURE

#endif  // SID_LIB_OS_H_