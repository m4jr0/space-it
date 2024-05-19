// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "event_system.h"

#include "system/memory_system.h"

#define SID_MAX_EVENT_TYPE_COUNT 64
#define SID_MAX_EVENT_LISTENER_COUNT 3
#define SID_MAX_EVENT_QUEUED_COUNT 128

typedef struct event_listeners {
  sid_event_callback list[SID_MAX_EVENT_LISTENER_COUNT];
  event_listener_index count;
} event_listeners;

typedef struct event_context {
  event_listeners listeners[SID_MAX_EVENT_TYPE_COUNT];
  sid_ring_queue event_queue;
  sid_event_id event_id_counter;
} event_context;

static event_context context;

void event_system_startup() {
  sid_ring_queue_generate(SID_MAX_EVENT_QUEUED_COUNT, sizeof(sid_event),
                          alignof(sid_event), SID_MEMORY_TAG_EVENT,
                          &context.event_queue);
  sid_zero_memory(&context.listeners, sizeof(context.listeners));
}

void event_system_shutdown() {
  sid_ring_queue_destroy(&context.event_queue, SID_MEMORY_TAG_EVENT);
}

void dispatch(const sid_event* event) {
  SID_ASSERT(event != SID_NULL, "Event provided is null!");
  SID_ASSERT(event->type >= 0 && event->type < SID_EVENT_TYPE_COUNT,
             "Unknown or unsupported event type: %d", event->type);

  uindex event_index = (uindex)event->type;
  const event_listeners* listeners = &context.listeners[event_index];

  for (event_listener_index i = 0; i < listeners->count; ++i) {
    listeners->list[i](event);
  }
}

sid_event_listener_id event_register(sid_event_callback callback,
                                     sid_event_type type) {
  SID_ASSERT(type >= 0 && type < SID_EVENT_TYPE_COUNT,
             "Unknown or unsupported event type: %d", type);
  uindex event_index = (uindex)type;
  event_listeners* listeners = &context.listeners[event_index];
  SID_ASSERT(listeners->count < SID_MAX_EVENT_LISTENER_COUNT,
             "Maximum number of event listeners reached!");

  sid_event_listener_id listener_id = 0;

  while (listener_id < SID_MAX_EVENT_LISTENER_COUNT) {
    if (listeners->list[listener_id] == SID_NULL) {
      listeners->list[listener_id] = callback;
      ++listeners->count;
      return listener_id;
    }

    ++listener_id;
  }

  SID_ASSERT(false,
             "Something really wrong happened while trying to register an "
             "event listener!");
  return SID_INVALID_EVENT_LISTENER_ID;
}

void event_unregister(sid_event_listener_id listener_id, sid_event_type type) {
  SID_ASSERT(type >= 0 && type < SID_EVENT_TYPE_COUNT,
             "Unknown or unsupported event type: %d", type);
  uindex event_index = (uindex)type;
  event_listeners* listeners = &context.listeners[event_index];
  SID_ASSERT(listener_id > 0 && listener_id < listeners->count,
             "Unknown listener ID!");
  listeners->list[listener_id] = SID_NULL;
  --listeners->count;
}

void event_fire(const sid_event* event) {
  sid_ring_queue_push(&context.event_queue, event);
}

void event_fire_now(const sid_event* event) { dispatch(event); }

void event_fire_all() {
  while (context.event_queue.entry_count > 0) {
    const sid_event* event = sid_ring_queue_get_front(&context.event_queue);
    dispatch(event);
    sid_ring_queue_pop(&context.event_queue);
  }
}

sid_event* event_generate_event() {
  sid_event* event =
      memory_allocate_two_frames(sizeof(sid_event), alignof(sid_event));
  event->id = context.event_id_counter;
  context.event_id_counter = (context.event_id_counter + 1) % SID_MAX_EVENT_ID;
  event->type = SID_EVENT_TYPE_UNKNOWN;
  return event;
}
