// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_SYSTEM_EVENT_SYSTEM_H_
#define SID_SYSTEM_EVENT_SYSTEM_H_

#include "sid/sid_lib.h"

typedef u8 event_listener_index;

void event_system_startup();
void event_system_shutdown();

sid_event_listener_id event_register(sid_event_callback callback,
                                     sid_event_type type);
void event_unregister(sid_event_listener_id listener_id, sid_event_type type);
void event_fire(const sid_event* event);
void event_fire_now(const sid_event* event);
void event_fire_all();

sid_event* event_generate_event();

#endif  // SID_SYSTEM_EVENT_SYSTEM_H_
