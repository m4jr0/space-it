// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_LIB_MATH_H_
#define SID_LIB_MATH_H_

#include "sid_precompile.h"

typedef struct vector {
  s32 x;
  s32 y;
} vector;

typedef enum sid_number_sign {
  SID_NUMBER_SIGN_UNKNOWN = 0,
  SID_NUMBER_SIGN_POSITIVE = 1,
  SID_NUMBER_SIGN_NEGATIVE = -1
} sid_number_sign;

SID_EXPORT f32 sid_magnitude(const vector* vector);
SID_EXPORT s32 sid_sqr_magnitude(const vector* vector);
SID_EXPORT f32 sid_sqrt_f32(f32 x);
SID_EXPORT f64 sid_sqrt_f64(f64 x);
SID_EXPORT s8 sid_abs_s8(s8 x);
SID_EXPORT s16 sid_abs_s16(s16 x);
SID_EXPORT s32 sid_abs_s32(s32 x);
SID_EXPORT s64 sid_abs_s64(s64 x);
SID_EXPORT f32 sid_abs_f32(f32 x);
SID_EXPORT f64 sid_abs_f64(f64 x);
SID_EXPORT sx sid_abs_sx(sx x);
SID_EXPORT fx sid_abs_fx(fx x);
SID_EXPORT u8 sid_min_u8(u8 a, u8 b);
SID_EXPORT u16 sid_min_u16(u16 a, u16 b);
SID_EXPORT u32 sid_min_u32(u32 a, u32 b);
SID_EXPORT u64 sid_min_u64(u64 a, u64 b);
SID_EXPORT uindex sid_min_uindex(uindex a, uindex b);
SID_EXPORT s8 sid_min_s8(s8 a, s8 b);
SID_EXPORT s16 sid_min_s16(s16 a, s16 b);
SID_EXPORT s32 sid_min_s32(s32 a, s32 b);
SID_EXPORT s64 sid_min_s64(s64 a, s64 b);
SID_EXPORT f32 sid_min_f32(f32 a, f32 b);
SID_EXPORT f64 sid_min_f64(f64 a, f64 b);
SID_EXPORT ux sid_min_ux(ux a, ux b);
SID_EXPORT sx sid_min_sx(sx a, sx b);
SID_EXPORT fx sid_min_fx(fx a, fx b);
SID_EXPORT u8 sid_max_u8(u8 a, u8 b);
SID_EXPORT u16 sid_max_u16(u16 a, u16 b);
SID_EXPORT u32 sid_max_u32(u32 a, u32 b);
SID_EXPORT u64 sid_max_u64(u64 a, u64 b);
SID_EXPORT uindex sid_max_uindex(uindex a, uindex b);
SID_EXPORT s8 sid_max_s8(s8 a, s8 b);
SID_EXPORT s16 sid_max_s16(s16 a, s16 b);
SID_EXPORT s32 sid_max_s32(s32 a, s32 b);
SID_EXPORT s64 sid_max_s64(s64 a, s64 b);
SID_EXPORT f32 sid_max_f32(f32 a, f32 b);
SID_EXPORT f64 sid_max_f64(f64 a, f64 b);
SID_EXPORT ux sid_max_ux(ux a, ux b);
SID_EXPORT sx sid_max_sx(sx a, sx b);
SID_EXPORT fx sid_max_fx(fx a, fx b);
SID_EXPORT u8 sid_clamp_u8(u8 x, u8 min, u8 max);
SID_EXPORT u16 sid_clamp_u16(u16 x, u16 min, u16 max);
SID_EXPORT u32 sid_clamp_u32(u32 x, u32 min, u32 max);
SID_EXPORT u64 sid_clamp_u64(u64 x, u64 min, u64 max);
SID_EXPORT s8 sid_clamp_s8(s8 x, s8 min, s8 max);
SID_EXPORT s16 sid_clamp_s16(s16 x, s16 min, s16 max);
SID_EXPORT s32 sid_clamp_s32(s32 x, s32 min, s32 max);
SID_EXPORT s64 sid_clamp_s64(s64 x, s64 min, s64 max);
SID_EXPORT f32 sid_clamp_f32(f32 x, f32 min, f32 max);
SID_EXPORT f64 sid_clamp_f64(f64 x, f64 min, f64 max);
SID_EXPORT ux sid_clamp_ux(ux x, ux min, ux max);
SID_EXPORT sx sid_clamp_sx(sx x, sx min, sx max);
SID_EXPORT fx sid_clamp_fx(fx x, fx min, fx max);
SID_EXPORT f32 sid_floor_f32(f32 x);
SID_EXPORT f64 sid_floor_f64(f64 x);
SID_EXPORT fx sid_floor_fx(fx x);
SID_EXPORT f32 sid_ceil_f32(f32 x);
SID_EXPORT f64 sid_ceil_f64(f64 x);
SID_EXPORT fx sid_ceil_fx(fx x);

#endif  // SID_LIB_MATH_H_
