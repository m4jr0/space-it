// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/log.h"

SID_EXPORT void sid_log(sid_log_level level, const schar* format, ...) {
  va_list args;
  va_start(args, format);

  switch (level) {
    default:
    case SID_LOG_LEVEL_DEBUG:
      printf("[DEBUG] ");
      break;
    case SID_LOG_LEVEL_INFO:
      printf("[INFO] ");
      break;
    case SID_LOG_LEVEL_WARNING:
      printf("[WARNING] ");
      break;
    case SID_LOG_LEVEL_ERROR:
      printf("[ERROR] ");
      break;
  }

  vprintf(format, args);
  putchar('\n');
  va_end(args);
}
