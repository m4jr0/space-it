// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "scene_system.h"

#include "system/animation_system.h"
#include "system/rendering_system.h"
#include "system/resource_system.h"

void scene_system_startup() {
  sid_animation_def_id def_id = sid_generate_animation_def_id("rene");
  sid_animation_id anim_id = sid_generate_animation_id("rene_animation_idle");
  sid_sprite_sheet_id sheet_id = sid_generate_sprite_sheet_id("rene");

  resource_load_animation_def(def_id);
  resource_load_animation(anim_id);
  resource_load_sprite_sheet(sheet_id);

  rendering_load_sprite_sheet(sheet_id);

  animation_load_animation_def(def_id);
  animation_load_animator(anim_id);
  animation_load_animation_def(def_id);
}

void scene_system_shutdown() {}

void scene_system_update() {}
