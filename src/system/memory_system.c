// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "memory_system.h"

#include "config.h"

typedef struct memory_context {
  sid_one_frame_allocator one_frame_allocator;
  sid_two_frame_allocator two_frame_allocator;
} memory_context;

static memory_context context;

static void memory_empty_free(void* ptr) { (void)ptr; }

void memory_system_startup() {
  sid_one_frame_allocator_generate(
      config_u32_get(SID_CONFIG_MEMORY_ONE_FRAME_ALLOCATOR_CAPACITY),
      SID_MEMORY_TAG_TEMPORARY, &context.one_frame_allocator);
  sid_two_frame_allocator_generate(
      config_u32_get(SID_CONFIG_MEMORY_TWO_FRAME_ALLOCATOR_CAPACITY),
      SID_MEMORY_TAG_TEMPORARY, &context.two_frame_allocator);

  sid_set_tmp_allocator_callbacks(
      memory_allocate_one_frame,
      // Nothing to do, ptr will be purged automatically after one frame.
      memory_empty_free);
}

void memory_system_shutdown() {
  sid_one_frame_allocator_destroy(&context.one_frame_allocator,
                                  SID_MEMORY_TAG_TEMPORARY);
  sid_two_frame_allocator_destroy(&context.two_frame_allocator,
                                  SID_MEMORY_TAG_TEMPORARY);
}

void memory_system_update() {
  sid_one_frame_allocator_clear(&context.one_frame_allocator);
  sid_two_frame_allocator_swap_frames(&context.two_frame_allocator);
  sid_two_frame_allocator_clear_current(&context.two_frame_allocator);
}

void* memory_allocate_one_frame(uindex size, u8 alignment) {
  return sid_one_frame_allocator_allocate(&context.one_frame_allocator, size,
                                          alignment);
}

void* memory_allocate_two_frames(uindex size, u8 alignment) {
  return sid_two_frame_allocator_allocate(&context.two_frame_allocator, size,
                                          alignment);
}