// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/memory.h"

#include "sid/file_system.h"
#include "sid/math.h"
#include "sid/string.h"

SID_EXPORT void sid_track_memory_operation(sid_memory_tag tag, uindex size,
                                           sid_number_sign sign) {
  // TODO(m4jr0): Use memory tag.
  (void)tag;
  (void)size;
  (void)sign;
}

#ifdef SID_DEBUG
#define SID_TRACK_MEMORY_OP(tag, size, sign) \
  sid_track_memory_operation(tag, size, sign)
#else
// Prevent compiler warning for unused variables.
#define SID_TRACK_MEMORY_OP(tag, size, sign) \
  do {                                       \
    (void)tag;                               \
    (void)size;                              \
    (void)sign;                              \
  } while (SID_FALSE)
#endif  // SID_DEBUG

SID_EXPORT void* sid_allocate(uindex size, sid_memory_tag tag) {
  return sid_allocate_aligned(size, 1, tag);
}

SID_EXPORT void* sid_allocate_aligned(uindex size, u16 alignment,
                                      sid_memory_tag tag) {
  uindex final_size = size + alignment;
  void* ptr = malloc(final_size);
  SID_POISON(ptr, final_size);

  SID_ASSERT(ptr != SID_NULL, "Could not allocate pointer!");
  u8* aligned_ptr = (u8*)sid_align_pointer(ptr, alignment);

  if (aligned_ptr == ptr) {
    aligned_ptr = (void*)((uptr)aligned_ptr + alignment);
  }

  uptr shift = (uptr)aligned_ptr - (uptr)ptr;
  SID_ASSERT(shift > 0 && shift <= SID_MAX_ALIGNMENT,
             "Invalid shift in memory allocation !Shift is " SID_UPTR_FORMAT
             ", but it must be "
             "between %u and %u.",
             shift, 0, SID_MAX_ALIGNMENT);

  aligned_ptr[-1] = shift & (u8)(SID_MAX_ALIGNMENT - 1);
  SID_TRACK_MEMORY_OP(tag, final_size, SID_NUMBER_SIGN_POSITIVE);
  return aligned_ptr;
}

SID_EXPORT void* sid_align_pointer(void* ptr, u16 alignment) {
  return (void*)sid_align_address((uptr)ptr, alignment);
}

SID_EXPORT uptr sid_align_address(uptr address, u16 alignment) {
  if (alignment == 0) {
    return address;
  }

  u16 mask = alignment - 1;

  SID_ASSERT((alignment & mask) == 0,
             "Bad alignment provided for address %p! Must be a power of 2",
             (void*)address);

  return (address + mask) & ~mask;
}

SID_EXPORT void sid_free(void* ptr, sid_memory_tag tag) {
  u8* aligned_ptr = (u8*)ptr;
  u16 shift = aligned_ptr[-1];

  if (shift == 0) {
    shift = SID_MAX_ALIGNMENT;
  }

  ptr = (void*)((uptr)aligned_ptr - shift);
  free(ptr);
  // TODO(m4jr0): Handle memory tracking properly.
  SID_TRACK_MEMORY_OP(tag, 0, SID_NUMBER_SIGN_NEGATIVE);
}

SID_EXPORT void sid_poison(void* ptr, uindex size) {
  SID_ASSERT(ptr != SID_NULL, "Pointer provided is null!");
  SID_ASSERT(size != 0, "Size provided is 0!");
  static u8 poison[4] = {0xef, 0xbe, 0xad, 0xde};

  uindex i = 0;
  u8* cur = (u8*)ptr;
  u8* top = cur + size;

  while (cur != top) {
    *cur = poison[i % 4];
    ++i;
    ++cur;
  }
}

SID_EXPORT void sid_copy_memory(void* dst, const void* src, uindex size) {
  memcpy(dst, src, size);
}

SID_EXPORT void sid_zero_memory(void* ptr, uindex size) {
  memset(ptr, 0, size);
}

#define BYTES_PER_LINE 16

SID_EXPORT void sid_dump_memory(void* ptr, uindex size, const tchar* path) {
  uindex hex_size = size * 3 + 1 + (size / BYTES_PER_LINE);
  schar* hex = (schar*)sid_allocate_tmp(hex_size, alignof(schar));
  u8* data = (u8*)ptr;

  uindex hex_index = 0;

  for (uindex i = 0; i < size; ++i) {
    sid_str_convert_hex(data[i], hex + hex_index, SID_NULL);
    hex_index += 2;
    hex[hex_index++] = ' ';

    if ((i + 1) % BYTES_PER_LINE == 0) {
      hex[hex_index++] = '\n';
    }
  }

  hex[hex_index] = '\0';

  sid_stream* stream = sid_open_file_binary_write(path);
  sid_write_file(hex, hex_size, stream);
  sid_close_file(stream);
  sid_free_tmp(hex);
}

void* sid_allocate_tmp_default(uindex size, u8 alignment) {
  return sid_allocate_aligned(size, alignment, SID_MEMORY_TAG_TEMPORARY);
}

void sid_free_tmp_default(void* ptr) {
  sid_free(ptr, SID_MEMORY_TAG_TEMPORARY);
}

static sid_tmp_allocator_allocate allocate_tmp = sid_allocate_tmp_default;
static sid_tmp_allocator_free free_tmp = sid_free_tmp_default;

SID_EXPORT void sid_set_tmp_allocator_callbacks(
    sid_tmp_allocator_allocate allocate_func,
    sid_tmp_allocator_free free_func) {
  allocate_tmp = allocate_func;
  free_tmp = free_func;
}

SID_EXPORT void* sid_allocate_tmp(uindex size, u8 alignment) {
  return allocate_tmp(size, alignment);
}

SID_EXPORT void sid_free_tmp(void* ptr) { free_tmp(ptr); }