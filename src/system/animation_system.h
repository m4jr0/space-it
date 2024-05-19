// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_SYSTEM_ANIMATION_SYSTEM_H_
#define SID_SYSTEM_ANIMATION_SYSTEM_H_

#include "sid/sid_lib.h"

#define SID_MAX_ANIMATOR_COUNT 256

typedef struct active_animators {
  const sid_animator* animators[SID_MAX_ANIMATOR_COUNT];
  uindex count;
} active_animators;

void animation_system_startup();
void animation_system_shutdown();
const active_animators* animation_system_update();

const sid_animation_def* animation_load_animation_def(sid_animation_def_id id);
void animation_unload_animation_def(sid_animation_def_id id);
const sid_animation_def* animation_get_animation_def(sid_animation_def_id id);
const sid_animator* animation_load_animator(sid_animation_id animation_id);
void animation_unload_animator(sid_animator_id id);
sid_animator* animation_get_animator(sid_animator_id id);

#endif  // SID_SYSTEM_ANIMATION_SYSTEM_H_
