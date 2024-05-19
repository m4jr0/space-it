// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "resource_system.h"

#include "system/animation_system.h"
#include "system/memory_system.h"

#define SID_MAX_SPRITE_SHEET_RESOURCE_COUNT 64
#define SID_MAX_ANIMATION_DEF_RESOURCE_COUNT 64
#define SID_MAX_ANIMATION_RESOURCE_COUNT 256

typedef struct resource_context {
  sid_fixed_hash_table sprite_sheets;
  sid_fixed_hash_table animation_defs;
  sid_fixed_hash_table animations;
} resource_context;

static resource_context context;

// Note: The returned value may change in the future, so use with caution.
static const tchar* resource_generate_tmp_path(sid_string_id resource_id) {
  const tchar* resources_path = SID_TCHAR("./resources/");
  const u8 resources_path_len = 12;
  const u8 string_id_max_len = 10;
  const u8 total_len = resources_path_len + string_id_max_len + 1;

  tchar* path =
      memory_allocate_one_frame(total_len * sizeof(tchar), alignof(tchar));

  sid_tstr_fill_with_secure(path, total_len, SID_TCHAR('0'));
  sid_tstr_copy(path, resources_path);
  uindex out_len;
  sid_tstr_convert_string_id(resource_id, path + resources_path_len, &out_len);
  return path;
}

static void resource_invalidate_sprite_sheet(
    sid_sprite_sheet_resource* resource) {
  resource->id = SID_INVALID_SPRITE_SHEET_ID;
  resource->channel_count = 0;
  resource->width = 0;
  resource->height = 0;
  resource->format = SID_TEXTURE_FORMAT_UNKNOWN;
  resource->size = 0;

  if (resource->data != SID_NULL) {
    sid_free(resource->data, SID_MEMORY_TAG_RESOURCE);
    resource->data = SID_NULL;
  }
}

static void resource_invalidate_animation_def(
    sid_animation_def_resource* resource) {
  resource->id = SID_INVALID_ANIMATION_DEF_ID;
  resource->sheet_id = SID_INVALID_SPRITE_SHEET_ID;
  resource->frame_count = 0;
  sid_zero_memory(resource->frames, SID_MAX_ANIMATION_FRAME_COUNT *
                                        sizeof(sid_animation_frame_resource));
}

static void resource_invalidate_animation(sid_animation_resource* resource) {
  resource->id = SID_INVALID_ANIMATION_ID;
  resource->def_id = SID_INVALID_ANIMATION_DEF_ID;
  resource->offset = 0;
  resource->length = 0;
}

void resource_system_startup() {
  sid_fixed_hashtable_generate_bytes(
      sizeof(sid_sprite_sheet_resource), alignof(sid_sprite_sheet_resource),
      SID_MAX_SPRITE_SHEET_RESOURCE_COUNT, SID_MEMORY_TAG_RESOURCE,
      &context.sprite_sheets);
  sid_fixed_hashtable_generate_bytes(
      sizeof(sid_animation_def_resource), alignof(sid_animation_def_resource),
      SID_MAX_ANIMATION_DEF_RESOURCE_COUNT, SID_MEMORY_TAG_RESOURCE,
      &context.animation_defs);
  sid_fixed_hashtable_generate_bytes(
      sizeof(sid_animation_resource), alignof(sid_animation_resource),
      SID_MAX_ANIMATION_RESOURCE_COUNT, SID_MEMORY_TAG_RESOURCE,
      &context.animations);

  {
    sid_sprite_sheet_resource invalid_resource = {0};
    resource_invalidate_sprite_sheet(&invalid_resource);
    sid_fixed_hashtable_fill(&context.sprite_sheets, &invalid_resource,
                             sizeof(sid_sprite_sheet_resource));
  }

  {
    sid_animation_def_resource invalid_resource = {0};
    resource_invalidate_animation_def(&invalid_resource);
    sid_fixed_hashtable_fill(&context.animation_defs, &invalid_resource,
                             sizeof(sid_animation_def_resource));
  }

  {
    sid_animation_resource invalid_resource = {0};
    resource_invalidate_animation(&invalid_resource);
    sid_fixed_hashtable_fill(&context.animations, &invalid_resource,
                             sizeof(sid_animation_resource));
  }
}

void resource_system_shutdown() {
  sid_sprite_sheet_resource* sheet_cursor =
      (sid_sprite_sheet_resource*)context.sprite_sheets.data;
  sid_sprite_sheet_resource* sheet_end =
      sheet_cursor + context.sprite_sheets.entry_count;

  while (sheet_cursor != sheet_end) {
    if (sheet_cursor->data != SID_NULL) {
      sid_free(sheet_cursor->data, SID_MEMORY_TAG_RESOURCE);
    }

    ++sheet_cursor;
  }

  sid_fixed_hashtable_destroy(&context.sprite_sheets, SID_MEMORY_TAG_RESOURCE);
  sid_fixed_hashtable_destroy(&context.animation_defs, SID_MEMORY_TAG_RESOURCE);
  sid_fixed_hashtable_destroy(&context.animations, SID_MEMORY_TAG_RESOURCE);
}

const sid_sprite_sheet_resource* resource_load_sprite_sheet(
    sid_sprite_sheet_id id) {
  sid_sprite_sheet_resource* resource = sid_fixed_hashtable_get_ref(
      &context.sprite_sheets, SID_HASHTABLE_STRING_ID_KEY(id));

  if (resource->id != SID_INVALID_SPRITE_SHEET_ID) {
    return resource;
  }

  sid_read_sprite_sheet_resource(resource_generate_tmp_path(id), resource);
  return resource;
}

void resource_unload_sprite_sheet(sid_sprite_sheet_id id) {
  sid_sprite_sheet_resource* resource = sid_fixed_hashtable_get_ref(
      &context.sprite_sheets, SID_HASHTABLE_STRING_ID_KEY(id));

  if (resource->id != SID_INVALID_SPRITE_SHEET_ID) {
    return;
  }

  resource_invalidate_sprite_sheet(resource);
}

const sid_sprite_sheet_resource* resource_get_sprite_sheet(
    sid_sprite_sheet_id id) {
  sid_sprite_sheet_resource* resource = sid_fixed_hashtable_get_ref(
      &context.sprite_sheets, SID_HASHTABLE_STRING_ID_KEY(id));

  SID_ASSERT(resource->id != SID_INVALID_SPRITE_SHEET_ID,
             "Tried to retrieve sprite sheet resource " SID_STRING_ID_FORMAT
             ", but it is not loaded!",
             id);

  return resource;
}

const sid_animation_def_resource* resource_load_animation_def(
    sid_animation_def_id id) {
  sid_animation_def_resource* resource = sid_fixed_hashtable_get_ref(
      &context.animation_defs, SID_HASHTABLE_STRING_ID_KEY(id));

  if (resource->id != SID_INVALID_ANIMATION_DEF_ID) {
    return resource;
  }

  sid_read_animation_def_resource(resource_generate_tmp_path(id), resource);
  return resource;
}

void resource_unload_animation_def(sid_animation_def_id id) {
  sid_animation_def_resource* resource = sid_fixed_hashtable_get_ref(
      &context.animation_defs, SID_HASHTABLE_STRING_ID_KEY(id));

  if (resource->id != SID_INVALID_ANIMATION_DEF_ID) {
    return;
  }

  resource_invalidate_animation_def(resource);
}

const sid_animation_def_resource* resource_get_animation_def(
    sid_animation_def_id id) {
  sid_animation_def_resource* resource = sid_fixed_hashtable_get_ref(
      &context.animation_defs, SID_HASHTABLE_STRING_ID_KEY(id));

  SID_ASSERT(
      resource->id != SID_INVALID_ANIMATION_DEF_ID,
      "Tried to retrieve animation definition resource " SID_STRING_ID_FORMAT
      ", but it is not loaded!",
      id);

  return resource;
}

const sid_animation_resource* resource_load_animation(sid_animation_id id) {
  sid_animation_resource* resource = sid_fixed_hashtable_get_ref(
      &context.animations, SID_HASHTABLE_STRING_ID_KEY(id));

  if (resource->id != SID_INVALID_ANIMATION_ID) {
    return resource;
  }

  sid_read_animation_resource(resource_generate_tmp_path(id), resource);
  return resource;
}

void resource_unload_animation(sid_animation_id id) {
  sid_animation_resource* resource = sid_fixed_hashtable_get_ref(
      &context.animations, SID_HASHTABLE_STRING_ID_KEY(id));

  if (resource->id != SID_INVALID_ANIMATION_ID) {
    return;
  }

  resource_invalidate_animation(resource);
}

const sid_animation_resource* resource_get_animation(sid_animation_id id) {
  sid_animation_resource* resource = sid_fixed_hashtable_get_ref(
      &context.animations, SID_HASHTABLE_STRING_ID_KEY(id));

  SID_ASSERT(resource->id != SID_INVALID_ANIMATION_ID,
             "Tried to retrieve animation resource " SID_STRING_ID_FORMAT
             ", but it is not loaded!",
             id);

  return resource;
}
