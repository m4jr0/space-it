// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_SYSTEM_TIME_SYSTEM_H_
#define SID_SYSTEM_TIME_SYSTEM_H_

#include "sid/sid_lib.h"

void time_system_startup();
void time_system_shutdown();
void time_system_update();

f64 time_get_now_millis();
f64 time_get_delta_time();
f64 time_get_fixed_delta_time();

#endif  // SID_SYSTEM_TIME_SYSTEM_H_
