// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_GRAPHICS_H_
#define SID_GRAPHICS_H_

#include "sid_precompile.h"

#include "sid/math.h"
#include "sid/string_id.h"

#define SID_SPRITE_SHEET_NAMESPACE "sprite_sheet"

// To be called outside of DLL (e.g. Rust, etc.).
SID_EXPORT const schar* sid_get_sprite_sheet_namespace();

typedef enum sid_texture_format {
  SID_TEXTURE_FORMAT_UNKNOWN = 0,
  SID_TEXTURE_FORMAT_RGB8,
  SID_TEXTURE_FORMAT_RGBA8
} sid_texture_format;

typedef struct sid_color {
  u8 r;
  u8 g;
  u8 b;
  u8 a;
} sid_color;

typedef struct sid_texture {
  sid_texture_format format;
  uindex size;
  void* data;
} sid_texture;

typedef sid_string_id sid_sprite_sheet_id;
#define SID_INVALID_SPRITE_SHEET_ID 0

SID_EXPORT sid_sprite_sheet_id sid_generate_sprite_sheet_id(const schar* path);

typedef u32 sid_sprite_sheet_dim;

typedef struct sid_sprite_sheet {
  sid_sprite_sheet_dim width;
  sid_sprite_sheet_dim height;
  sid_sprite_sheet_id id;
  sid_texture texture;
} sid_sprite_sheet;

#endif  // SID_GRAPHICS_H_
