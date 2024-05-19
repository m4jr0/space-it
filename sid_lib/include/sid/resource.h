// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_LIB_RESOURCE_H_
#define SID_LIB_RESOURCE_H_

#include "sid_precompile.h"

#include "sid/animation.h"
#include "sid/graphics.h"
#include "sid/string_id.h"

typedef struct sid_sprite_sheet_resource {
  u8 channel_count;
  sid_animation_frame_dim width;
  sid_animation_frame_dim height;
  sid_sprite_sheet_id id;
  sid_texture_format format;
  uindex size;
  u8* data;
} sid_sprite_sheet_resource;

SID_EXPORT void sid_read_sprite_sheet_resource(
    const tchar* path, sid_sprite_sheet_resource* resource);

typedef struct sid_animation_frame_resource {
  sid_animation_frame_pos pos;
  sid_animation_frame_dims dims;
  sid_animation_frame_duration duration;
} sid_animation_frame_resource;

typedef struct sid_animation_def_resource {
  sid_animation_frame_index frame_count;
  sid_animation_frame_resource frames[SID_MAX_ANIMATION_FRAME_COUNT];
  sid_animation_def_id id;
  sid_sprite_sheet_id sheet_id;
} sid_animation_def_resource;

typedef struct sid_animation_resource {
  sid_animation_frame_index offset;
  sid_animation_frame_index length;
  sid_animation_id id;
  sid_animation_def_id def_id;
} sid_animation_resource;

SID_EXPORT void sid_read_animation_def_resource(
    const tchar* path, sid_animation_def_resource* resource);

SID_EXPORT void sid_read_animation_resource(const tchar* path,
                                            sid_animation_resource* resource);

#endif  // SID_LIB_RESOURCE_H_