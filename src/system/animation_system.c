// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "animation_system.h"

#include "system/rendering_system.h"
#include "system/resource_system.h"
#include "system/time_system.h"

typedef struct animation_context {
  sid_fixed_hash_table animation_defs;
  sid_fixed_hash_table animators;
  active_animators active_animators;
} animation_context;

#define SID_MAX_ANIMATION_DEF_COUNT 64

#define SID_HASHTABLE_ANIMATOR_KEY(id) \
  SID_HASHTABLE_BYTES_KEY(&id, sizeof(sid_animator_id))

static animation_context context;
static sid_animator_id animator_id_counter = 0;

static void animation_invalidate_animation_def(sid_animation_def* def) {
  def->id = SID_INVALID_ANIMATION_DEF_ID;
  def->sheet = SID_NULL;
  def->frame_count = 0;
  sid_zero_memory(def->frames,
                  SID_MAX_ANIMATION_FRAME_COUNT * sizeof(sid_animation_frame));
}

static void animation_invalidate_animator(sid_animator* animator) {
  animator->id = SID_INVALID_ANIMATOR_ID;
  animator->def = SID_NULL;
  animator->animation.id = SID_INVALID_ANIMATION_ID;
  animator->animation.offset = 0;
  animator->animation.length = 0;
  animator->current_frame = 0;
  animator->loop = SID_FALSE;
  animator->active = SID_FALSE;
  animator->flipped = SID_FALSE;
}

static void animation_update_animator(f64 time, sid_animator* animator) {
  animator->current_frame_time += time;
  const sid_animation_frame* frame = sid_get_animation_frame(animator);

  if (animator->current_frame_time - animator->last_frame_time <
      frame->duration) {
    return;
  }

  animator->last_frame_time = animator->current_frame_time;
  animator->current_frame =
      (animator->current_frame + 1) % animator->animation.length;
}

void animation_system_startup() {
  context.active_animators.animators[0] = SID_NULL;
  context.active_animators.count = 0;

  sid_fixed_hashtable_generate_bytes(
      sizeof(sid_animation_def), alignof(sid_animation_def),
      SID_MAX_ANIMATION_DEF_COUNT, SID_MEMORY_TAG_ANIMATION,
      &context.animation_defs);

  sid_fixed_hashtable_generate_bytes(
      sizeof(sid_animator), alignof(sid_animator), SID_MAX_ANIMATOR_COUNT,
      SID_MEMORY_TAG_ANIMATION, &context.animators);

  {
    sid_animation_def invalid = {0};
    animation_invalidate_animation_def(&invalid);
    sid_fixed_hashtable_fill(&context.animation_defs, &invalid,
                             sizeof(sid_animation_def));
  }

  {
    sid_animator invalid = {0};
    animation_invalidate_animator(&invalid);
    sid_fixed_hashtable_fill(&context.animators, &invalid,
                             sizeof(sid_animator));
  }
}

void animation_system_shutdown() {
  sid_fixed_hashtable_destroy(&context.animation_defs,
                              SID_MEMORY_TAG_ANIMATION);
  sid_fixed_hashtable_destroy(&context.animators, SID_MEMORY_TAG_ANIMATION);

  context.active_animators.animators[0] = SID_NULL;
  context.active_animators.count = 0;
}

const active_animators* animation_system_update() {
  sid_animator* animator_cursor = (sid_animator*)context.animators.data;
  sid_animator* animator_end = animator_cursor + context.animators.entry_count;
  --animator_cursor;

  context.active_animators.animators[0] = SID_NULL;
  context.active_animators.count = 0;

  f64 time = time_get_delta_time();

  while (animator_cursor != animator_end) {
    ++animator_cursor;

    if (animator_cursor->id == SID_INVALID_ANIMATOR_ID) {
      continue;
    }

    if (context.active_animators.animators[0] == SID_NULL) {
      context.active_animators.animators[context.active_animators.count] =
          animator_cursor;
    }

    ++context.active_animators.count;
    animation_update_animator(time, animator_cursor);
  }

  return &context.active_animators;
}

const sid_animation_def* animation_load_animation_def(sid_animation_def_id id) {
  sid_animation_def* def = sid_fixed_hashtable_get_ref(
      &context.animation_defs, SID_HASHTABLE_STRING_ID_KEY(id));

  if (def->id != SID_INVALID_ANIMATION_DEF_ID) {
    return def;
  }

  const sid_animation_def_resource* resource = resource_get_animation_def(id);
  def->id = resource->id;
  def->sheet = rendering_get_sprite_sheet(resource->sheet_id);
  def->frame_count = resource->frame_count;

  for (uindex i = 0; i < def->frame_count; ++i) {
    def->frames[i].pos = resource->frames[i].pos;
    def->frames[i].dims = resource->frames[i].dims;
    def->frames[i].duration = resource->frames[i].duration;
  }

  return def;
}

void animation_unload_animation_def(sid_animation_def_id id) {
  sid_animation_def* def = sid_fixed_hashtable_get_ref(
      &context.animation_defs, SID_HASHTABLE_STRING_ID_KEY(id));

  if (def->id != SID_INVALID_ANIMATION_DEF_ID) {
    return;
  }

  animation_invalidate_animation_def(def);
}

const sid_animation_def* animation_get_animation_def(sid_animation_def_id id) {
  sid_animation_def* def = sid_fixed_hashtable_get_ref(
      &context.animation_defs, SID_HASHTABLE_STRING_ID_KEY(id));

  SID_ASSERT(def->id != SID_INVALID_ANIMATOR_ID,
             "Tried to retrieve animation definition " SID_STRING_ID_FORMAT
             ", but it is not loaded!",
             id);

  return def;
}

const sid_animator* animation_load_animator(sid_animation_id animation_id) {
  sid_animator_id id = ++animator_id_counter;
  sid_animator* animator = sid_fixed_hashtable_get_ref(
      &context.animators, SID_HASHTABLE_ANIMATOR_KEY(id));

  if (animator->id != SID_INVALID_ANIMATOR_ID) {
    return animator;
  }

  const sid_animation_resource* resource = resource_get_animation(animation_id);

  animator->loop = SID_TRUE;
  animator->active = SID_TRUE;
  animator->flipped = SID_FALSE;
  animator->current_frame = 0;
  animator->id = id;

  animator->animation.id = resource->id;
  animator->animation.offset = resource->offset;
  animator->animation.length = resource->length;

  animator->def = animation_get_animation_def(resource->def_id);

  return animator;
}

void animation_unload_animator(sid_animator_id id) {
  sid_animator* animator = sid_fixed_hashtable_get_ref(
      &context.animators, SID_HASHTABLE_ANIMATOR_KEY(id));

  if (animator->id != SID_INVALID_ANIMATOR_ID) {
    return;
  }

  animation_invalidate_animator(animator);
}

sid_animator* animation_get_animator(sid_animator_id id) {
  sid_animator* animator = sid_fixed_hashtable_get_ref(
      &context.animators, SID_HASHTABLE_ANIMATOR_KEY(id));

  SID_ASSERT(animator->id != SID_INVALID_ANIMATOR_ID,
             "Tried to retrieve animator " SID_STRING_ID_FORMAT
             ", but it is not loaded!",
             id);

  return animator;
}