// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_SYSTEM_RESOURCE_SYSTEM_H_
#define SID_SYSTEM_RESOURCE_SYSTEM_H_

#include "sid/sid_lib.h"

void resource_system_startup();
void resource_system_shutdown();

const sid_sprite_sheet_resource* resource_load_sprite_sheet(
    sid_sprite_sheet_id id);
void resource_unload_sprite_sheet(sid_sprite_sheet_id id);
const sid_sprite_sheet_resource* resource_get_sprite_sheet(
    sid_sprite_sheet_id id);
const sid_animation_def_resource* resource_load_animation_def(
    sid_animation_def_id id);
void resource_unload_animation_def(sid_animation_def_id id);
const sid_animation_def_resource* resource_get_animation_def(
    sid_animation_def_id id);
const sid_animation_resource* resource_load_animation(sid_animation_id id);
void resource_unload_animation(sid_animation_id id);
const sid_animation_resource* resource_get_animation(sid_animation_id id);

#endif  // SID_SYSTEM_RESOURCE_SYSTEM_H_
