// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_DEBUG_H_
#define SID_DEBUG_H_

#include "sid_precompile.h"

#ifndef SID_DEBUG
#define SID_ASSERT(assertion, ...)
#else
#define SID_ASSERT(assertion, ...) \
  do {                             \
    b8 is_ok = assertion;          \
                                   \
    if (!is_ok) {                  \
      SID_LOG_ERROR(__VA_ARGS__);  \
    }                              \
                                   \
    assert(is_ok);                 \
  } while (SID_FALSE)
#endif  // !SID_DEBUG
#endif  // SID_DEBUG_H_
