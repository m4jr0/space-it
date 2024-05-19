// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "physics_system.h"

#include "config.h"
#include "system/event_system.h"
#include "system/memory_system.h"
#include "system/time_system.h"

typedef struct physics_context {
  u32 frame_rate;
  u32 counter;
  u32 max_frame_rate;
  f64 current_time;
  f64 fixed_delta_time;
} physics_context;

static physics_context context;

void physics_system_startup() {
  context.frame_rate = config_u32_get(SID_CONFIG_PHYSICS_REFRESH_RATE);
  context.counter = 0;
  context.current_time = 0.0;
  context.fixed_delta_time = time_get_fixed_delta_time();
  context.max_frame_rate =
      (u32)(sid_floor_f64(1.0 / context.fixed_delta_time) * 1000.0);
}

void physics_system_shutdown() {
  context.frame_rate = 0;
  context.counter = 0;
  context.max_frame_rate = 0;
  context.current_time = 0.0;
  context.fixed_delta_time = 0.0;
}

void physics_system_update(f64* lag) {
  f64 local_lag = *lag;

  if (context.current_time > 1000.0) {
    context.frame_rate = context.counter;
    context.current_time = 0.0;
    context.counter = 0;
  }

  context.current_time += time_get_delta_time();

  while (local_lag > context.fixed_delta_time) {
    memory_system_update();

    if (context.max_frame_rate > 0 &&
        context.counter == context.max_frame_rate) {
      *lag = 0.0;
      return;
    }

    ++context.counter;
    local_lag -= context.fixed_delta_time;
    event_fire_all();
  }

  *lag = local_lag;
}
