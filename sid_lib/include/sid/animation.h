// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_ANIMATION_H_
#define SID_ANIMATION_H_

#include "sid_precompile.h"

#include "sid/graphics.h"

#define SID_ANIMATION_NAMESPACE "animation"
#define SID_ANIMATION_DEF_NAMESPACE "animation_definition"
#define SID_MAX_ANIMATION_FRAME_COUNT 256

// To be called outside of DLL (e.g. Rust, etc.).
SID_EXPORT const schar* sid_get_animation_namespace();
SID_EXPORT const schar* sid_get_animation_def_namespace();
SID_EXPORT u16 sid_get_max_animation_frame_count();

typedef u16 sid_animation_frame_coord;

typedef struct sid_animation_frame_pos {
  sid_animation_frame_coord x;
  sid_animation_frame_coord y;
} sid_animation_frame_pos;

typedef u16 sid_animation_frame_dim;

typedef struct sid_animation_frame_dims {
  sid_animation_frame_dim width;
  sid_animation_frame_dim height;
} sid_animation_frame_dims;

typedef u16 sid_animation_frame_duration;

typedef struct sid_animation_frame {
  sid_animation_frame_pos pos;
  sid_animation_frame_dims dims;
  sid_animation_frame_duration duration;
} sid_animation_frame;

typedef sid_string_id sid_animation_def_id;
#define SID_INVALID_ANIMATION_DEF_ID 0

SID_EXPORT sid_animation_def_id
sid_generate_animation_def_id(const schar* path);

typedef u16 sid_animation_frame_index;

typedef struct sid_animation_def {
  sid_animation_frame_index frame_count;
  sid_animation_frame frames[SID_MAX_ANIMATION_FRAME_COUNT];
  sid_animation_def_id id;
  const sid_sprite_sheet* sheet;
} sid_animation_def;

typedef sid_string_id sid_animation_id;
#define SID_INVALID_ANIMATION_ID 0

SID_EXPORT sid_animation_id sid_generate_animation_id(const schar* path);

typedef struct sid_animation {
  sid_animation_id id;
  sid_animation_frame_index offset;
  sid_animation_frame_index length;
} sid_animation;

typedef u16 sid_animator_id;
#define SID_INVALID_ANIMATOR_ID 0

typedef struct sid_animator {
  b8 loop;
  b8 active;
  b8 flipped;
  sid_animator_id id;
  vector position;
  sid_animation_frame_index current_frame;
  sid_animation animation;
  f64 last_frame_time;
  f64 current_frame_time;
  const sid_animation_def* def;
} sid_animator;

SID_EXPORT const sid_animation_frame* sid_get_animation_frame(
    const sid_animator* animator);

#endif  // SID_ANIMATION_H_
