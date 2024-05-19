// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/allocator.h"

SID_EXPORT void sid_stack_allocator_generate(
    uindex capacity, sid_memory_tag tag, sid_stack_allocator* out_allocator) {
  SID_ASSERT(out_allocator != SID_NULL, "Allocator provided is null!");
  SID_ASSERT(
      out_allocator->root == SID_NULL && out_allocator->marker == SID_NULL,
      "Allocator seems to be already generated!");
  out_allocator->capacity = capacity;
  SID_ASSERT(out_allocator->capacity > 0, "Capacity provided is 0!");
  out_allocator->root =
      sid_allocate_aligned(out_allocator->capacity, alignof(u8), tag);
  out_allocator->marker = out_allocator->root;
}

SID_EXPORT void sid_stack_allocator_destroy(sid_stack_allocator* allocator,
                                            sid_memory_tag tag) {
  if (allocator->root != SID_NULL) {
    sid_free(allocator->root, tag);
    allocator->root = SID_NULL;
  }

  allocator->size = 0;
  allocator->capacity = 0;
  allocator->marker = SID_NULL;
}

SID_EXPORT void* sid_stack_allocator_allocate(sid_stack_allocator* allocator,
                                              uindex size, u8 alignment) {
  SID_ASSERT(allocator != SID_NULL, "Allocator provided is null!");
  SID_ASSERT(allocator->root != SID_NULL && allocator->marker != SID_NULL,
             "Allocator provided is not generated!");
  u8* ptr = (u8*)sid_align_pointer(allocator->marker, alignment);
  SID_ASSERT(ptr + size <= allocator->root + allocator->capacity,
             "Max capacity reached!");
  allocator->marker = ptr + size;
  return ptr;
}

SID_EXPORT void sid_stack_allocator_clear(sid_stack_allocator* allocator) {
  SID_ASSERT(allocator != SID_NULL, "Allocator provided is null!");
  SID_ASSERT(allocator->root != SID_NULL && allocator->marker != SID_NULL,
             "Allocator provided is not generated!");
  allocator->marker = allocator->root;
}

SID_EXPORT uindex sid_stack_allocator_get_size(sid_stack_allocator* allocator) {
  SID_ASSERT(allocator != SID_NULL, "Allocator provided is null!");
  SID_ASSERT(allocator->root != SID_NULL && allocator->marker != SID_NULL,
             "Allocator provided is not generated!");
  return allocator->marker - allocator->root;
}

SID_EXPORT void sid_one_frame_allocator_generate(
    uindex capacity, sid_memory_tag tag,
    sid_one_frame_allocator* out_allocator) {
  sid_stack_allocator_generate(capacity, tag, out_allocator);
}

SID_EXPORT void sid_one_frame_allocator_destroy(
    sid_one_frame_allocator* allocator, sid_memory_tag tag) {
  sid_stack_allocator_destroy(allocator, tag);
}

SID_EXPORT void* sid_one_frame_allocator_allocate(
    sid_one_frame_allocator* allocator, uindex size, u8 alignment) {
  return sid_stack_allocator_allocate(allocator, size, alignment);
}

SID_EXPORT void sid_one_frame_allocator_clear(
    sid_one_frame_allocator* allocator) {
  sid_stack_allocator_clear(allocator);
}

SID_EXPORT uindex
sid_one_frame_allocator_get_size(sid_one_frame_allocator* allocator) {
  return sid_stack_allocator_get_size(allocator);
}

SID_EXPORT void sid_two_frame_allocator_generate(
    uindex total_capacity, sid_memory_tag tag,
    sid_two_frame_allocator* out_allocator) {
  SID_ASSERT(out_allocator != SID_NULL, "Allocator provided is null!");
  SID_ASSERT(total_capacity > 0, "Total capacity provided is 0!");
  sid_stack_allocator_generate(total_capacity / 2, tag,
                               &out_allocator->stacks[0]);
  sid_stack_allocator_generate(total_capacity / 2, tag,
                               &out_allocator->stacks[1]);
}

SID_EXPORT void sid_two_frame_allocator_destroy(
    sid_two_frame_allocator* allocator, sid_memory_tag tag) {
  SID_ASSERT(allocator != SID_NULL, "Allocator provided is null!");
  sid_stack_allocator_destroy(&allocator->stacks[0], tag);
  sid_stack_allocator_destroy(&allocator->stacks[1], tag);
  sid_zero_memory(allocator, sizeof(allocator));
}

SID_EXPORT void* sid_two_frame_allocator_allocate(
    sid_two_frame_allocator* allocator, uindex size, u8 alignment) {
  SID_ASSERT(allocator != SID_NULL, "Allocator provided is null!");
  return sid_stack_allocator_allocate(
      &allocator->stacks[allocator->current_stack], size, alignment);
}

SID_EXPORT void sid_two_frame_allocator_swap_frames(
    sid_two_frame_allocator* allocator) {
  SID_ASSERT(allocator != SID_NULL, "Allocator provided is null!");
  allocator->current_stack = (u8)!allocator->current_stack;
}

SID_EXPORT void sid_two_frame_allocator_clear_current(
    sid_two_frame_allocator* allocator) {
  SID_ASSERT(allocator != SID_NULL, "Allocator provided is null!");
  sid_stack_allocator_clear(&allocator->stacks[allocator->current_stack]);
}

SID_EXPORT uindex
sid_two_frame_allocator_get_current_size(sid_two_frame_allocator* allocator) {
  SID_ASSERT(allocator != SID_NULL, "Allocator provided is null!");
  return sid_stack_allocator_get_size(
      &allocator->stacks[allocator->current_stack]);
}

SID_EXPORT uindex
sid_two_frame_allocator_get_total_size(sid_two_frame_allocator* allocator) {
  SID_ASSERT(allocator != SID_NULL, "Allocator provided is null!");
  return sid_stack_allocator_get_size(&allocator->stacks[0]) +
         sid_stack_allocator_get_size(&allocator->stacks[1]);
}
