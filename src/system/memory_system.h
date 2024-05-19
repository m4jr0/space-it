// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_SYSTEM_MEMORY_SYSTEM_H_
#define SID_SYSTEM_MEMORY_SYSTEM_H_

#include "sid/sid_lib.h"

void memory_system_startup();
void memory_system_shutdown();
void memory_system_update();

void* memory_allocate_one_frame(uindex size, u8 alignment);
void* memory_allocate_two_frames(uindex size, u8 alignment);

#endif  // SID_SYSTEM_MEMORY_SYSTEM_H_
