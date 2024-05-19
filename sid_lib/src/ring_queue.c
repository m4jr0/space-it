// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/ring_queue.h"

SID_EXPORT void sid_ring_queue_generate(uindex capacity, uindex entry_size,
                                        u16 entry_alignment, sid_memory_tag tag,
                                        sid_ring_queue* out_queue) {
  SID_ASSERT(out_queue != SID_NULL, "Queue provided is null!");
  out_queue->capacity = capacity;
  out_queue->entry_count = 0;
  out_queue->entry_size = entry_size;

  // TODO(m4jr0): Give the option to use a custom allocator.
  out_queue->data = sid_allocate_aligned(
      out_queue->entry_size * out_queue->capacity, entry_alignment, tag);
}

SID_EXPORT void sid_ring_queue_destroy(sid_ring_queue* queue,
                                       sid_memory_tag tag) {
  SID_ASSERT(queue != SID_NULL, "Queue provided is null!");

  if (queue->data != SID_NULL) {
    sid_free(queue->data, tag);
    queue->data = SID_NULL;
  }

  queue->capacity = 0;
  queue->entry_size = 0;
  queue->entry_count = 0;
  queue->head = 0;
}

SID_EXPORT void sid_ring_queue_push(sid_ring_queue* queue, const void* value) {
  SID_ASSERT(queue != SID_NULL, "Queue provided is null!");
  SID_ASSERT(queue->data != SID_NULL, "Queue provided has no data!");
  SID_ASSERT(queue->entry_count < queue->capacity, "Queue provided is full!");
  uptr offset_index = ((queue->head + queue->entry_count++) % queue->capacity);
  sid_copy_memory(((u8*)queue->data) + offset_index * queue->entry_size, value,
                  queue->entry_size);
}

SID_EXPORT void* sid_ring_queue_get_front(const sid_ring_queue* queue) {
  SID_ASSERT(queue != SID_NULL, "Queue provided is null!");
  SID_ASSERT(queue->data != SID_NULL, "Queue provided has no data!");
  SID_ASSERT(queue->entry_count > 0, "Queue provided is empty!");
  return ((u8*)queue->data) + queue->head * queue->entry_size;
}

SID_EXPORT void sid_ring_queue_pop(sid_ring_queue* queue) {
  SID_ASSERT(queue != SID_NULL, "Queue provided is null!");
  SID_ASSERT(queue->data != SID_NULL, "Queue provided has no data!");
  SID_ASSERT(queue->entry_count > 0, "Queue provided is empty!");
  queue->head = (queue->head + 1) % queue->capacity;
  --queue->entry_count;
}

SID_EXPORT void sid_ring_queue_clear(sid_ring_queue* queue) {
  SID_ASSERT(queue != SID_NULL, "Queue provided is null!");
  SID_ASSERT(queue->data != SID_NULL, "Queue provided has no data!");
  queue->head = 0;
  queue->entry_count = 0;
}
