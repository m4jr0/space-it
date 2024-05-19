// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_SYSTEM_PHYSICS_SYSTEM_H_
#define SID_SYSTEM_PHYSICS_SYSTEM_H_

#include "sid/sid_lib.h"

void physics_system_startup();
void physics_system_shutdown();
void physics_system_update(f64* lag);

#endif  // SID_SYSTEM_PHYSICS_SYSTEM_H_
