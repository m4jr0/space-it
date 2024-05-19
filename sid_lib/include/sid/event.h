// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_EVENT_H_
#define SID_EVENT_H_

#include "sid_precompile.h"

typedef enum sid_event_type {
  SID_EVENT_TYPE_UNKNOWN = -1,
  SID_EVENT_TYPE_GAME_EXIT,
  SID_EVENT_TYPE_KEY_DOWN,
  SID_EVENT_TYPE_KEY_UP,
  SID_EVENT_TYPE_MOUSE_DOWN,
  SID_EVENT_TYPE_MOUSE_UP,
  SID_EVENT_TYPE_MOUSE_MOVE,
  SID_EVENT_TYPE_GAMEPAD_DOWN,
  SID_EVENT_TYPE_GAMEPAD_UP,
} sid_event_type;

#define SID_EVENT_TYPE_COUNT 8

typedef union sid_event_value {
  b8 b8;
  u8 u8;
  u16 u16;
  u32 u32;
  u64 u64;
  s8 s8;
  s16 s16;
  s32 s32;
  s64 s64;
  f32 f32;
  f64 f64;
  ux ux;
  sx sx;
  fx fx;
} sid_event_value;

#define SID_MAX_EVENT_VALUE_COUNT 5

typedef u32 sid_event_id;
#define SID_MAX_EVENT_ID SID_U32_MAX

typedef struct sid_event {
  sid_event_id id;  // Debugging ID.
  sid_event_type type;
  sid_event_value values[SID_MAX_EVENT_VALUE_COUNT];
} sid_event;

typedef void (*sid_event_callback)(const sid_event* event);

typedef u16 sid_event_listener_id;
#define SID_INVALID_EVENT_LISTENER_ID SID_U16_MAX

#endif  // SID_EVENT_H_
