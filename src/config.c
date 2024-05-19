// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "config.h"

static config* config_ptr;

void config_startup(config* config) {
  config_ptr = config;

  sid_fixed_hashtable_generate_string(
      sizeof(config_value), alignof(config_value), SID_CONFIG_VALUE_COUNT,
      SID_MEMORY_TAG_CONFIG, &config_ptr->values);

  // TODO(m4jr0): Read values from a file.
  config_u32_set(SID_CONFIG_MEMORY_ONE_FRAME_ALLOCATOR_CAPACITY, 1024);
  config_u32_set(SID_CONFIG_MEMORY_TWO_FRAME_ALLOCATOR_CAPACITY, 2048);
  config_f64_set(SID_CONFIG_GAME_MS_PER_UPDATE, 16.66);
  config_u8_set(SID_CONFIG_CLEAR_COLOR_R, 200);
  config_u8_set(SID_CONFIG_CLEAR_COLOR_G, 200);
  config_u8_set(SID_CONFIG_CLEAR_COLOR_B, 200);
  config_u16_set(SID_CONFIG_WINDOW_WIDTH, 800);
  config_u16_set(SID_CONFIG_WINDOW_HEIGHT, 600);
  config_str_set(SID_CONFIG_GAME_TITLE, "Space it, dummy!");
  config_u32_set(SID_CONFIG_PHYSICS_REFRESH_RATE, 60);
}

void config_destroy() {
  sid_fixed_hashtable_destroy(&config_ptr->values, SID_MEMORY_TAG_CONFIG);
  config_ptr = SID_NULL;
}

void config_value_get(const schar* key, config_value* out_value) {
  SID_ASSERT(out_value != SID_NULL, "Out value provided is null!");
  sid_fixed_hashtable_get(&config_ptr->values, SID_HASHTABLE_STRING_KEY(key),
                          (void**)&out_value);
}

void config_value_set(const schar* key, const config_value* value) {
  sid_fixed_hashtable_set(&config_ptr->values, SID_HASHTABLE_STRING_KEY(key),
                          value);
}

const schar* config_str_get(const schar* key) {
  config_value* conf_value = (config_value*)sid_fixed_hashtable_get_ref(
      &config_ptr->values, SID_HASHTABLE_STRING_KEY(key));
  return conf_value->str_value;
}

void config_str_set(const schar* key, const schar* value) {
  SID_ASSERT(value != SID_NULL, "Value provided is null!");
  uindex i = 0;
  config_value conf_value;

  while (value[i] != '\0' && i < SID_CONFIG_VALUE_STR_MAX_LEN) {
    conf_value.str_value[i] = value[i];
    ++i;
  }

  if (i >= SID_CONFIG_VALUE_STR_MAX_LEN) {
    SID_LOG_ERROR(
        "String value for key %s is too long. Length provided is greater than "
        "%zu. Value will be trimmed.",
        value, SID_CONFIG_VALUE_STR_MAX_LEN);
    i = SID_CONFIG_VALUE_STR_MAX_LEN;
  }

  conf_value.str_value[i] = '\0';
  config_value_set(key, &conf_value);
}

const tchar* config_tstr_get(const schar* key) {
  config_value* conf_value = (config_value*)sid_fixed_hashtable_get_ref(
      &config_ptr->values, SID_HASHTABLE_STRING_KEY(key));

#ifdef SID_WIDE_TCHAR
  return conf_value->wstr_value;
#else
  return conf_value->str_value;
#endif  // SID_WIDE_TCHAR
}

void config_tstr_set(const schar* key, const tchar* value) {
  SID_ASSERT(value != SID_NULL, "Value provided is null!");
  uindex i = 0;
  config_value conf_value;

  while (value[i] != SID_TCHAR('\0') && i < SID_CONFIG_VALUE_STR_MAX_LEN) {
#ifdef SID_WIDE_TCHAR
    conf_value.wstr_value[i] = value[i];
#else
    conf_value.str_value[i] = value[i];
#endif  // SID_WIDE_TCHAR
    ++i;
  }

  if (i >= SID_CONFIG_VALUE_STR_MAX_LEN) {
    SID_LOG_ERROR(
        "String value for key %s is too long. Length provided is greater than "
        "%zu. Value will be trimmed.",
        value, SID_CONFIG_VALUE_STR_MAX_LEN);
    i = SID_CONFIG_VALUE_STR_MAX_LEN;
  }

  conf_value.str_value[i] = SID_TCHAR('\0');
  config_value_set(key, &conf_value);
}

u8 config_u8_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.u8_value;
}

void config_u8_set(const schar* key, u8 value) {
  config_value conf_value = {.u8_value = value};
  config_value_set(key, &conf_value);
}

u16 config_u16_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.u16_value;
}

void config_u16_set(const schar* key, u16 value) {
  config_value conf_value = {.u16_value = value};
  config_value_set(key, &conf_value);
}

u32 config_u32_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.u32_value;
}

void config_u32_set(const schar* key, u32 value) {
  config_value conf_value = {.u32_value = value};
  config_value_set(key, &conf_value);
}

u64 config_u64_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.u64_value;
}

void config_u64_set(const schar* key, u64 value) {
  config_value conf_value = {.u64_value = value};
  config_value_set(key, &conf_value);
}

s8 config_s8_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.u8_value;
}

void config_s8_set(const schar* key, s8 value) {
  config_value conf_value = {.s8_value = value};
  config_value_set(key, &conf_value);
}

s16 config_s16_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.s16_value;
}

void config_s16_set(const schar* key, s16 value) {
  config_value conf_value = {.s16_value = value};
  config_value_set(key, &conf_value);
}

s32 config_s32_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.s32_value;
}

void config_s32_set(const schar* key, s32 value) {
  config_value conf_value = {.s32_value = value};
  config_value_set(key, &conf_value);
}

s64 config_s64_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.s64_value;
}

void config_s64_set(const schar* key, s64 value) {
  config_value conf_value = {.s64_value = value};
  config_value_set(key, &conf_value);
}

f32 config_f32_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.f32_value;
}

void config_f32_set(const schar* key, f32 value) {
  config_value conf_value = {.f32_value = value};
  config_value_set(key, &conf_value);
}

f64 config_f64_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.f64_value;
}

void config_f64_set(const schar* key, f64 value) {
  config_value conf_value = {.f64_value = value};
  config_value_set(key, &conf_value);
}

uindex config_uindex_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.uindex_value;
}

void config_uindex_set(const schar* key, uindex value) {
  config_value conf_value = {.uindex_value = value};
  config_value_set(key, &conf_value);
}

ux config_ux_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.ux_value;
}

void config_ux_set(const schar* key, ux value) {
  config_value conf_value = {.ux_value = value};
  config_value_set(key, &conf_value);
}

sx config_sx_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.sx_value;
}

void config_sx_set(const schar* key, sx value) {
  config_value conf_value = {.sx_value = value};
  config_value_set(key, &conf_value);
}

fx config_fx_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.fx_value;
}

void config_fx_set(const schar* key, fx value) {
  config_value conf_value = {.fx_value = value};
  config_value_set(key, &conf_value);
}

b8 config_b8_get(const schar* key) {
  config_value conf_value;
  config_value_get(key, &conf_value);
  return conf_value.b8_value;
}

void config_b8_set(const schar* key, b8 value) {
  config_value conf_value = {.b8_value = value};
  config_value_set(key, &conf_value);
}