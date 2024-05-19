// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_SYSTEM_RENDERING_SYSTEM_H_
#define SID_SYSTEM_RENDERING_SYSTEM_H_

#include "sid/sid_lib.h"

typedef struct rendering_frame {
  f64 interpolation;
  const sid_animator* const* animators;
  uindex animator_count;
} rendering_frame;

void rendering_system_startup();
void rendering_system_shutdown();
void rendering_system_update(const rendering_frame* frame);

const sid_sprite_sheet* rendering_load_sprite_sheet(sid_sprite_sheet_id id);
void rendering_unload_sprite_sheet(sid_sprite_sheet_id id);
const sid_sprite_sheet* rendering_get_sprite_sheet(sid_sprite_sheet_id id);

#endif  // SID_SYSTEM_RENDERING_SYSTEM_H_
