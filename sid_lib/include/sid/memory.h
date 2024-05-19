// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_LIB_MEMORY_H_
#define SID_LIB_MEMORY_H_

#include "sid_precompile.h"

typedef enum sid_memory_tag {
  SID_MEMORY_TAG_UNKNOWN = 0,
  SID_MEMORY_TAG_CONFIG,
  SID_MEMORY_TAG_TEMPORARY,
  SID_MEMORY_TAG_EVENT,
  SID_MEMORY_TAG_RESOURCE,
  SID_MEMORY_TAG_RENDERING,
  SID_MEMORY_TAG_ANIMATION,
  SID_MEMORY_TAG_DEBUG,
} sid_memory_tag;

#define SID_MAX_ALIGNMENT 256

SID_EXPORT void* sid_allocate(uindex size, sid_memory_tag tag);
SID_EXPORT void* sid_allocate_aligned(uindex size, u16 alignment,
                                      sid_memory_tag tag);
SID_EXPORT void* sid_align_pointer(void* ptr, u16 alignment);
SID_EXPORT uptr sid_align_address(uptr address, u16 alignment);
SID_EXPORT void sid_free(void* ptr, sid_memory_tag tag);
SID_EXPORT void sid_poison(void* ptr, uindex size);
SID_EXPORT void sid_copy_memory(void* dst, const void* src, uindex size);
SID_EXPORT void sid_zero_memory(void* ptr, uindex size);
SID_EXPORT void sid_dump_memory(void* ptr, uindex size, const tchar* path);

#ifdef SID_POISON_ALLOCATIONS
#define SID_POISON(ptr, size) sid_poison(ptr, size)
#else
#define SID_POISON(ptr, size)
#endif  // SID_POISON_ALLOCATIONS

typedef void* (*sid_tmp_allocator_allocate)(uindex size, u8 alignment);
typedef void (*sid_tmp_allocator_free)(void* ptr);

SID_EXPORT void sid_set_tmp_allocator_callbacks(
    sid_tmp_allocator_allocate allocate_func, sid_tmp_allocator_free free_func);

SID_EXPORT void* sid_allocate_tmp(uindex size, u8 alignment);
SID_EXPORT void sid_free_tmp(void* ptr);

#endif  // SID_LIB_MEMORY_H_
