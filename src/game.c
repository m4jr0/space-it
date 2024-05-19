// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "game.h"

#include "system/animation_system.h"
#include "system/event_system.h"
#include "system/input_system.h"
#include "system/memory_system.h"
#include "system/physics_system.h"
#include "system/rendering_system.h"
#include "system/resource_system.h"
#include "system/scene_system.h"
#include "system/time_system.h"

typedef struct game_state {
  b8 running;
  f64 lag;
  config config;
} game_state;

static game_state game;

static void startup_systems() {
  memory_system_startup();
  event_system_startup();
  time_system_startup();
  input_system_startup();
  resource_system_startup();
  physics_system_startup();
  animation_system_startup();
  rendering_system_startup();
  scene_system_startup();
}

static void shutdown_systems() {
  scene_system_shutdown();
  rendering_system_shutdown();
  animation_system_shutdown();
  physics_system_shutdown();
  resource_system_shutdown();
  input_system_shutdown();
  time_system_shutdown();
  event_system_shutdown();
  memory_system_shutdown();
}

static void on_game_exit(const sid_event* event) {
  (void)event;
  game.running = SID_FALSE;
}

static void game_startup() {
  SID_ASSERT(game.running == SID_FALSE, "Game is already running!");
  game.running = SID_FALSE;
  config_startup(&game.config);
  startup_systems();
  event_register(on_game_exit, SID_EVENT_TYPE_GAME_EXIT);
}

static void game_run() {
  game.running = SID_TRUE;
  game.lag = 0.0;

  while (game.running == SID_TRUE) {
    time_system_update();
    game.lag += time_get_delta_time();

    physics_system_update(&game.lag);
    const active_animators* active_animators = animation_system_update();

    rendering_frame frame = {0};
    frame.animators = active_animators->animators;
    frame.animator_count = active_animators->count;
    rendering_system_update(&frame);
  }
}

static void game_destroy() {
  shutdown_systems(game);
  config_destroy();
}

void game_generate() {
  game_startup();
  game_run(game);
  game_destroy(game);
}
