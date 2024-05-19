// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_LIB_DEFINE_H_
#define SID_LIB_DEFINE_H_

#include "os.h"

// String.
#ifdef SID_WINDOWS
#define SID_WIDE_TCHAR
#endif  // SID_WINDOWS

// Path.
#define SID_NORMALIZE_PATHS

// Rendering.
#ifdef SID_DEBUG
#define SID_POISON_ALLOCATIONS
#endif  // SID_DEBUG

#endif  // SID_LIB_DEFINE_H_
