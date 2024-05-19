// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/graphics.h"

#include "sid/hash.h"

SID_EXPORT
const schar* sid_get_sprite_sheet_namespace() {
  return SID_SPRITE_SHEET_NAMESPACE;
}

sid_sprite_sheet_id sid_generate_sprite_sheet_id(const schar* path) {
  return sid_generate_namespaced_string_id(SID_SPRITE_SHEET_NAMESPACE, path);
}