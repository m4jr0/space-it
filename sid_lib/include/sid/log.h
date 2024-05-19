// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_LIB_LOG_H_
#define SID_LIB_LOG_H_

#include "sid_precompile.h"

typedef enum sid_log_level {
  SID_LOG_LEVEL_DEBUG,
  SID_LOG_LEVEL_INFO,
  SID_LOG_LEVEL_WARNING,
  SID_LOG_LEVEL_ERROR
} sid_log_level;

SID_EXPORT void sid_log(sid_log_level level, const schar* format, ...);

#ifndef SID_DEBUG
#define SID_LOG_DEBUG(...)
#define SID_LOG_INFO(...)
#define SID_LOG_WARNING(...)
#else
#define SID_LOG_DEBUG(...) sid_log(SID_LOG_LEVEL_DEBUG, __VA_ARGS__)
#define SID_LOG_INFO(...) sid_log(SID_LOG_LEVEL_INFO, __VA_ARGS__)
#define SID_LOG_WARNING(...) sid_log(SID_LOG_LEVEL_WARNING, __VA_ARGS__)
#endif  // !SID_DEBUG

#define SID_LOG_ERROR(...) sid_log(SID_LOG_LEVEL_ERROR, __VA_ARGS__)

#endif  // SID_LIB_LOG_H_
