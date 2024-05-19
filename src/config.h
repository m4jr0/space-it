// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_CONFIG_H_
#define SID_CONFIG_H_

#include "sid/sid_lib.h"

#define SID_CONFIG_VALUE_STR_MAX_LEN 260

typedef union config_value {
  schar str_value[SID_CONFIG_VALUE_STR_MAX_LEN + 1];
  wchar wstr_value[(SID_CONFIG_VALUE_STR_MAX_LEN + 1) * sizeof(wchar)];
  u8 u8_value;
  u16 u16_value;
  u32 u32_value;
  u64 u64_value;
  s8 s8_value;
  s16 s16_value;
  s32 s32_value;
  s64 s64_value;
  f32 f32_value;
  f64 f64_value;
  uindex uindex_value;
  ux ux_value;
  sx sx_value;
  fx fx_value;
  b8 b8_value;
} config_value;

typedef struct config {
  sid_fixed_hash_table values;
} config;

#define SID_CONFIG_VALUE_COUNT 100
#define SID_CONFIG_MEMORY_ONE_FRAME_ALLOCATOR_CAPACITY \
  "memory_one_frame_allocator_capacity"
#define SID_CONFIG_MEMORY_TWO_FRAME_ALLOCATOR_CAPACITY \
  "memory_two_frame_allocator_capacity"

#define SID_CONFIG_GAME_MS_PER_UPDATE "game_ms_per_update"
#define SID_CONFIG_CLEAR_COLOR_R "clear_color_r"
#define SID_CONFIG_CLEAR_COLOR_G "clear_color_g"
#define SID_CONFIG_CLEAR_COLOR_B "clear_color_b"
#define SID_CONFIG_WINDOW_WIDTH "window_width"
#define SID_CONFIG_WINDOW_HEIGHT "window_height"
#define SID_CONFIG_GAME_TITLE "game_title"
#define SID_CONFIG_PHYSICS_REFRESH_RATE "physics_refresh_rate"

void config_startup(config* config);
void config_destroy();
void config_value_get(const schar* key, config_value* out_value);
void config_value_set(const schar* key, const config_value* value);
void config_str_set(const schar* key, const schar* value);
const schar* config_str_get(const schar* key);
void config_tstr_set(const schar* key, const tchar* value);
const tchar* config_tstr_get(const schar* key);
u8 config_u8_get(const schar* key);
void config_u8_set(const schar* key, u8 value);
u16 config_u16_get(const schar* key);
void config_u16_set(const schar* key, u16 value);
u32 config_u32_get(const schar* key);
void config_u32_set(const schar* key, u32 value);
u64 config_u64_get(const schar* key);
void config_u64_set(const schar* key, u64 value);
s16 config_s16_get(const schar* key);
void config_s16_set(const schar* key, s16 value);
s32 config_s32_get(const schar* key);
void config_s32_set(const schar* key, s32 value);
s64 config_s64_get(const schar* key);
void config_s64_set(const schar* key, s64 value);
f32 config_f32_get(const schar* key);
void config_f32_set(const schar* key, f32 value);
f64 config_f64_get(const schar* key);
void config_f64_set(const schar* key, f64 value);
uindex config_uindex_get(const schar* key);
void config_uindex_set(const schar* key, uindex value);
ux config_ux_get(const schar* key);
void config_ux_set(const schar* key, ux value);
sx config_sx_get(const schar* key);
void config_sx_set(const schar* key, sx value);
fx config_fx_get(const schar* key);
void config_fx_set(const schar* key, fx value);
b8 config_b8_get(const schar* key);
void config_b8_set(const schar* key, b8 value);

#endif  // SID_CONFIG_H_
