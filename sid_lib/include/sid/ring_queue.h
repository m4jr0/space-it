// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_RING_QUEUE_H_
#define SID_RING_QUEUE_H_

#include "sid_precompile.h"

typedef struct sid_ring_queue {
  uindex capacity;
  uindex entry_size;
  uindex entry_count;
  uindex head;
  void* data;
} sid_ring_queue;

SID_EXPORT void sid_ring_queue_generate(uindex capacity, uindex entry_size,
                                        u16 entry_alignment, sid_memory_tag tag,
                                        sid_ring_queue* out_queue);
SID_EXPORT void sid_ring_queue_destroy(sid_ring_queue* queue,
                                       sid_memory_tag tag);
SID_EXPORT void sid_ring_queue_push(sid_ring_queue* queue, const void* value);
SID_EXPORT void* sid_ring_queue_get_front(const sid_ring_queue* queue);
SID_EXPORT void sid_ring_queue_pop(sid_ring_queue* queue);
SID_EXPORT void sid_ring_queue_clear(sid_ring_queue* queue);

#endif  // SID_RING_QUEUE_H_
