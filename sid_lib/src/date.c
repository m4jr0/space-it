// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/date.h"

SID_EXPORT f64 sid_get_real_now_millis() {
#ifdef SID_WINDOWS
  struct __timeb64 time;
  _ftime64_s(&time);
  return (1000.0 * time.time + time.millitm);
#else
  struct timespec time;
  clock_gettime(CLOCK_REALTIME, &time);
  return (f64)time.tv_sec * 1000.0 + (f64)time.tv_nsec / 1000000.0;
#endif  // SID_WINDOWS
}