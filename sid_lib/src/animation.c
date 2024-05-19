// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/animation.h"

#include "sid/string_id.h"

SID_EXPORT
const schar* sid_get_animation_namespace() { return SID_ANIMATION_NAMESPACE; }

SID_EXPORT const schar* sid_get_animation_def_namespace() {
  return SID_ANIMATION_DEF_NAMESPACE;
}

SID_EXPORT u16 sid_get_max_animation_frame_count() {
  return SID_MAX_ANIMATION_FRAME_COUNT;
}

sid_animation_def_id sid_generate_animation_def_id(const schar* path) {
  return sid_generate_namespaced_string_id(SID_ANIMATION_DEF_NAMESPACE, path);
}

SID_EXPORT sid_animation_def_id sid_generate_animation_id(const schar* path) {
  return sid_generate_namespaced_string_id(SID_ANIMATION_NAMESPACE, path);
}

SID_EXPORT const sid_animation_frame* sid_get_animation_frame(
    const sid_animator* animator) {
  return &animator->def->frames[animator->current_frame];
}
