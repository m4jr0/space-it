// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "time_system.h"

#include "config.h"

typedef struct time_context {
  f64 fixed_delta_time;
  f64 current_time;
  f64 previous_time;
  f64 delta_time;
  f64 time_scale;
} time_context;

static time_context context;

void time_system_startup() {
  context.fixed_delta_time =
      sid_ceil_f64(config_f64_get(SID_CONFIG_GAME_MS_PER_UPDATE) * 100.0) /
      100.0;

  context.current_time = 0.0;
  context.previous_time = sid_get_real_now_millis();
  context.delta_time = 0.0;
  context.time_scale = 1.0;
}

void time_system_shutdown() {
  context.fixed_delta_time = 0.0;
  context.current_time = 0.0;
  context.previous_time = 0.0;
  context.delta_time = 0.0;
  context.time_scale = 1.0;
}

void time_system_update() {
  context.current_time = time_get_now_millis();
  context.delta_time = context.current_time - context.previous_time;
  context.previous_time = context.current_time;
}

f64 time_get_now_millis() {
  f64 delta_time = sid_get_real_now_millis() - context.previous_time;
  f64 time_to_add = delta_time * context.time_scale;
  return context.previous_time + time_to_add;
}

f64 time_get_delta_time() { return context.delta_time; }

f64 time_get_fixed_delta_time() { return context.fixed_delta_time; }
