// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_ALLOCATOR_H_
#define SID_ALLOCATOR_H_

#include "sid_precompile.h"

#include "sid/memory.h"

typedef u8* sid_stack_allocator_marker;

typedef struct sid_stack_allocator {
  uindex size;
  uindex capacity;
  u8* root;
  sid_stack_allocator_marker marker;
} sid_stack_allocator;

SID_EXPORT void sid_stack_allocator_generate(
    uindex capacity, sid_memory_tag tag, sid_stack_allocator* out_allocator);
SID_EXPORT void sid_stack_allocator_destroy(sid_stack_allocator* allocator,
                                            sid_memory_tag tag);
SID_EXPORT void* sid_stack_allocator_allocate(sid_stack_allocator* allocator,
                                              uindex size, u8 alignment);
SID_EXPORT void sid_stack_allocator_clear(sid_stack_allocator* allocator);
SID_EXPORT uindex sid_stack_allocator_get_size(sid_stack_allocator* allocator);

typedef sid_stack_allocator sid_one_frame_allocator;

SID_EXPORT void sid_one_frame_allocator_generate(
    uindex capacity, sid_memory_tag tag,
    sid_one_frame_allocator* out_allocator);
SID_EXPORT void sid_one_frame_allocator_destroy(
    sid_one_frame_allocator* allocator, sid_memory_tag tag);
SID_EXPORT void* sid_one_frame_allocator_allocate(
    sid_one_frame_allocator* allocator, uindex size, u8 alignment);
SID_EXPORT void sid_one_frame_allocator_clear(
    sid_one_frame_allocator* allocator);
SID_EXPORT uindex
sid_one_frame_allocator_get_size(sid_one_frame_allocator* allocator);

typedef struct sid_two_frame_allocator {
  u8 current_stack;
  sid_stack_allocator stacks[2];
} sid_two_frame_allocator;

SID_EXPORT void sid_two_frame_allocator_generate(
    uindex total_capacity, sid_memory_tag tag,
    sid_two_frame_allocator* out_allocator);
SID_EXPORT void sid_two_frame_allocator_destroy(
    sid_two_frame_allocator* allocator, sid_memory_tag tag);
SID_EXPORT void* sid_two_frame_allocator_allocate(
    sid_two_frame_allocator* allocator, uindex size, u8 alignment);
SID_EXPORT void sid_two_frame_allocator_swap_frames(
    sid_two_frame_allocator* allocator);
SID_EXPORT void sid_two_frame_allocator_clear_current(
    sid_two_frame_allocator* allocator);
SID_EXPORT uindex
sid_two_frame_allocator_get_current_size(sid_two_frame_allocator* allocator);
SID_EXPORT uindex
sid_two_frame_allocator_get_total_size(sid_two_frame_allocator* allocator);

#endif  // SID_ALLOCATOR_H_
