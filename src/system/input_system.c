// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "input_system.h"

#include "SDL2/SDL.h"

#include "system/event_system.h"

static sid_key_code get_key_code_from_sdl(s32 sdl_key_code) {
  switch (sdl_key_code) {
    case SDLK_UNKNOWN:
      return SID_KEY_CODE_UNKNOWN;
    case SDLK_SPACE:
      return SID_KEY_CODE_SPACE;
    case SDLK_QUOTE:
      return SID_KEY_CODE_APOSTROPHE;
    case SDLK_COMMA:
      return SID_KEY_CODE_COMMA;
    case SDLK_MINUS:
      return SID_KEY_CODE_MINUS;
    case SDLK_PERIOD:
      return SID_KEY_CODE_PERIOD;
    case SDLK_SLASH:
      return SID_KEY_CODE_SLASH;
    case SDLK_0:
      return SID_KEY_CODE_ZERO;
    case SDLK_1:
      return SID_KEY_CODE_ONE;
    case SDLK_2:
      return SID_KEY_CODE_TWO;
    case SDLK_3:
      return SID_KEY_CODE_THREE;
    case SDLK_4:
      return SID_KEY_CODE_FOUR;
    case SDLK_5:
      return SID_KEY_CODE_FIVE;
    case SDLK_6:
      return SID_KEY_CODE_SIX;
    case SDLK_7:
      return SID_KEY_CODE_SEVEN;
    case SDLK_8:
      return SID_KEY_CODE_EIGHT;
    case SDLK_9:
      return SID_KEY_CODE_NINE;
    case SDLK_SEMICOLON:
      return SID_KEY_CODE_SEMICOLON;
    case SDLK_EQUALS:
      return SID_KEY_CODE_EQUAL;
    case SDLK_a:
      return SID_KEY_CODE_A;
    case SDLK_b:
      return SID_KEY_CODE_B;
    case SDLK_c:
      return SID_KEY_CODE_C;
    case SDLK_d:
      return SID_KEY_CODE_D;
    case SDLK_e:
      return SID_KEY_CODE_E;
    case SDLK_f:
      return SID_KEY_CODE_F;
    case SDLK_g:
      return SID_KEY_CODE_G;
    case SDLK_h:
      return SID_KEY_CODE_H;
    case SDLK_i:
      return SID_KEY_CODE_I;
    case SDLK_j:
      return SID_KEY_CODE_J;
    case SDLK_k:
      return SID_KEY_CODE_K;
    case SDLK_l:
      return SID_KEY_CODE_L;
    case SDLK_m:
      return SID_KEY_CODE_M;
    case SDLK_n:
      return SID_KEY_CODE_N;
    case SDLK_o:
      return SID_KEY_CODE_O;
    case SDLK_p:
      return SID_KEY_CODE_P;
    case SDLK_q:
      return SID_KEY_CODE_Q;
    case SDLK_r:
      return SID_KEY_CODE_R;
    case SDLK_s:
      return SID_KEY_CODE_S;
    case SDLK_t:
      return SID_KEY_CODE_T;
    case SDLK_u:
      return SID_KEY_CODE_U;
    case SDLK_v:
      return SID_KEY_CODE_V;
    case SDLK_w:
      return SID_KEY_CODE_W;
    case SDLK_x:
      return SID_KEY_CODE_X;
    case SDLK_y:
      return SID_KEY_CODE_Y;
    case SDLK_z:
      return SID_KEY_CODE_Z;
    case SDLK_LEFTBRACKET:
      return SID_KEY_CODE_LEFT_BRACKET;
    case SDLK_BACKSLASH:
      return SID_KEY_CODE_BACKSLASH;
    case SDLK_RIGHTBRACKET:
      return SID_KEY_CODE_RIGHT_BRACKET;
    case SDLK_BACKQUOTE:
      return SID_KEY_CODE_GRAVE_ACCENT;
    case SDLK_ESCAPE:
      return SID_KEY_CODE_ESCAPE;
    case SDLK_RETURN:
      return SID_KEY_CODE_ENTER;
    case SDLK_TAB:
      return SID_KEY_CODE_TAB;
    case SDLK_BACKSPACE:
      return SID_KEY_CODE_BACKSPACE;
    case SDLK_INSERT:
      return SID_KEY_CODE_INSERT;
    case SDLK_DELETE:
      return SID_KEY_CODE_DEL;
    case SDLK_RIGHT:
      return SID_KEY_CODE_RIGHT;
    case SDLK_LEFT:
      return SID_KEY_CODE_LEFT;
    case SDLK_DOWN:
      return SID_KEY_CODE_DOWN;
    case SDLK_UP:
      return SID_KEY_CODE_UP;
    case SDLK_PAGEUP:
      return SID_KEY_CODE_PAGE_UP;
    case SDLK_PAGEDOWN:
      return SID_KEY_CODE_PAGE_DOWN;
    case SDLK_HOME:
      return SID_KEY_CODE_HOME;
    case SDLK_END:
      return SID_KEY_CODE_END;
    case SDLK_CAPSLOCK:
      return SID_KEY_CODE_CAPS_LOCK;
    case SDLK_SCROLLLOCK:
      return SID_KEY_CODE_SCROLL_LOCK;
    case SDLK_NUMLOCKCLEAR:
      return SID_KEY_CODE_NUM_LOCK;
    case SDLK_PRINTSCREEN:
      return SID_KEY_CODE_PRINT_SCREEN;
    case SDLK_PAUSE:
      return SID_KEY_CODE_PAUSE;
    case SDLK_F1:
      return SID_KEY_CODE_F1;
    case SDLK_F2:
      return SID_KEY_CODE_F2;
    case SDLK_F3:
      return SID_KEY_CODE_F3;
    case SDLK_F4:
      return SID_KEY_CODE_F4;
    case SDLK_F5:
      return SID_KEY_CODE_F5;
    case SDLK_F6:
      return SID_KEY_CODE_F6;
    case SDLK_F7:
      return SID_KEY_CODE_F7;
    case SDLK_F8:
      return SID_KEY_CODE_F8;
    case SDLK_F9:
      return SID_KEY_CODE_F9;
    case SDLK_F10:
      return SID_KEY_CODE_F10;
    case SDLK_F11:
      return SID_KEY_CODE_F11;
    case SDLK_F12:
      return SID_KEY_CODE_F12;
    case SDLK_F13:
      return SID_KEY_CODE_F13;
    case SDLK_F14:
      return SID_KEY_CODE_F14;
    case SDLK_F15:
      return SID_KEY_CODE_F15;
    case SDLK_F16:
      return SID_KEY_CODE_F16;
    case SDLK_F17:
      return SID_KEY_CODE_F17;
    case SDLK_F18:
      return SID_KEY_CODE_F18;
    case SDLK_F19:
      return SID_KEY_CODE_F19;
    case SDLK_F20:
      return SID_KEY_CODE_F20;
    case SDLK_F21:
      return SID_KEY_CODE_F21;
    case SDLK_F22:
      return SID_KEY_CODE_F22;
    case SDLK_F23:
      return SID_KEY_CODE_F23;
    case SDLK_F24:
      return SID_KEY_CODE_F24;
    case SDLK_KP_0:
      return SID_KEY_CODE_KP_0;
    case SDLK_KP_1:
      return SID_KEY_CODE_KP_1;
    case SDLK_KP_2:
      return SID_KEY_CODE_KP_2;
    case SDLK_KP_3:
      return SID_KEY_CODE_KP_3;
    case SDLK_KP_4:
      return SID_KEY_CODE_KP_4;
    case SDLK_KP_5:
      return SID_KEY_CODE_KP_5;
    case SDLK_KP_6:
      return SID_KEY_CODE_KP_6;
    case SDLK_KP_7:
      return SID_KEY_CODE_KP_7;
    case SDLK_KP_8:
      return SID_KEY_CODE_KP_8;
    case SDLK_KP_9:
      return SID_KEY_CODE_KP_9;
    case SDLK_KP_DECIMAL:
      return SID_KEY_CODE_KP_DECIMAL;
    case SDLK_KP_DIVIDE:
      return SID_KEY_CODE_KP_DIVIDE;
    case SDLK_KP_MULTIPLY:
      return SID_KEY_CODE_KP_MULTIPLY;
    case SDLK_KP_MINUS:
      return SID_KEY_CODE_KP_SUBTRACT;
    case SDLK_KP_PLUS:
      return SID_KEY_CODE_KP_ADD;
    case SDLK_KP_ENTER:
      return SID_KEY_CODE_KP_ENTER;
    case SDLK_KP_EQUALS:
      return SID_KEY_CODE_KP_EQUAL;
    case SDLK_LSHIFT:
      return SID_KEY_CODE_LEFT_SHIFT;
    case SDLK_LCTRL:
      return SID_KEY_CODE_LEFT_CONTROL;
    case SDLK_LALT:
      return SID_KEY_CODE_LEFT_ALT;
    case SDLK_LGUI:
      return SID_KEY_CODE_LEFT_SUPER;
    case SDLK_RSHIFT:
      return SID_KEY_CODE_RIGHT_SHIFT;
    case SDLK_RCTRL:
      return SID_KEY_CODE_RIGHT_CONTROL;
    case SDLK_RALT:
      return SID_KEY_CODE_RIGHT_ALT;
    case SDLK_RGUI:
      return SID_KEY_CODE_RIGHT_SUPER;
    case SDLK_MENU:
      return SID_KEY_CODE_MENU;
    default:
      return SID_KEY_CODE_UNKNOWN;
  }
}

static sid_key_mod get_key_mod_from_sdl(s32 sdl_key_mod) {
  sid_key_mod mods = SID_KEY_MOD_NONE;
  if (sdl_key_mod & KMOD_SHIFT) mods = SID_KEY_MOD_SHIFT;
  if (sdl_key_mod & KMOD_CTRL) mods = SID_KEY_MOD_CONTROL;
  if (sdl_key_mod & KMOD_ALT) mods = SID_KEY_MOD_ALT;
  if (sdl_key_mod & KMOD_GUI) mods = SID_KEY_MOD_SUPER;
  if (sdl_key_mod & KMOD_CAPS) mods = SID_KEY_MOD_CAPS_LOCK;
  if (sdl_key_mod & KMOD_NUM) mods = SID_KEY_MOD_NUM_LOCK;
  return mods;
}

static sid_mouse_button get_mouse_button_from_sdl(s32 sdl_mouse_button) {
  switch (sdl_mouse_button) {
    case SDL_BUTTON_LEFT:
      return SID_MOUSE_BUTTON_LEFT;
    case SDL_BUTTON_RIGHT:
      return SID_MOUSE_BUTTON_RIGHT;
    case SDL_BUTTON_MIDDLE:
      return SID_MOUSE_BUTTON_MIDDLE;
    case SDL_BUTTON_X1:
      return SID_MOUSE_BUTTON_OTHER_1;
    case SDL_BUTTON_X2:
      return SID_MOUSE_BUTTON_OTHER_2;
    default:
      return SID_MOUSE_BUTTON_UNKNOWN;
  }
}

static sid_gamepad_button get_gamepad_button_from_sdl(s32 sdl_gamepad_button) {
  switch (sdl_gamepad_button) {
    case SDL_CONTROLLER_BUTTON_A:
      return SID_GAMEPAD_BUTTON_A;
    case SDL_CONTROLLER_BUTTON_B:
      return SID_GAMEPAD_BUTTON_B;
    case SDL_CONTROLLER_BUTTON_X:
      return SID_GAMEPAD_BUTTON_X;
    case SDL_CONTROLLER_BUTTON_Y:
      return SID_GAMEPAD_BUTTON_Y;
    case SDL_CONTROLLER_BUTTON_BACK:
      return SID_GAMEPAD_BUTTON_BACK;
    case SDL_CONTROLLER_BUTTON_GUIDE:
      return SID_GAMEPAD_BUTTON_GUIDE;
    case SDL_CONTROLLER_BUTTON_START:
      return SID_GAMEPAD_BUTTON_START;
    case SDL_CONTROLLER_BUTTON_LEFTSTICK:
      return SID_GAMEPAD_BUTTON_LEFT_STICK;
    case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
      return SID_GAMEPAD_BUTTON_RIGHT_STICK;
    case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
      return SID_GAMEPAD_BUTTON_LEFT_SHOULDER;
    case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
      return SID_GAMEPAD_BUTTON_RIGHT_SHOULDER;
    case SDL_CONTROLLER_BUTTON_DPAD_UP:
      return SID_GAMEPAD_BUTTON_DPAD_UP;
    case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
      return SID_GAMEPAD_BUTTON_DPAD_DOWN;
    case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
      return SID_GAMEPAD_BUTTON_DPAD_LEFT;
    case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
      return SID_GAMEPAD_BUTTON_DPAD_RIGHT;
    case SDL_CONTROLLER_BUTTON_MISC1:
      return SID_GAMEPAD_BUTTON_MISC;
    case SDL_CONTROLLER_BUTTON_PADDLE1:
      return SID_GAMEPAD_BUTTON_PADDLE_1;
    case SDL_CONTROLLER_BUTTON_PADDLE2:
      return SID_GAMEPAD_BUTTON_PADDLE_2;
    case SDL_CONTROLLER_BUTTON_PADDLE3:
      return SID_GAMEPAD_BUTTON_PADDLE_3;
    case SDL_CONTROLLER_BUTTON_PADDLE4:
      return SID_GAMEPAD_BUTTON_PADDLE_4;
    case SDL_CONTROLLER_BUTTON_TOUCHPAD:
      return SID_GAMEPAD_BUTTON_TOUCHPAD;
    case SDL_CONTROLLER_BUTTON_MAX:
      return SID_GAMEPAD_BUTTON_MAX;
    default:
      return SID_GAMEPAD_BUTTON_UNKNOWN;
  }
}

static sid_event* input_try_generate_event(const SDL_Event* sdl_event) {
  if (sdl_event->type == SDL_QUIT) {
    sid_event* event = event_generate_event();
    event->type = SID_EVENT_TYPE_GAME_EXIT;
    return event;
  }

  if (sdl_event->type == SDL_KEYDOWN || sdl_event->type == SDL_KEYUP) {
    sid_event* event = event_generate_event();
    event->type = sdl_event->type == SDL_KEYDOWN ? SID_EVENT_TYPE_KEY_DOWN
                                                 : SID_EVENT_TYPE_KEY_UP;
    event->values[0].s32 = get_key_code_from_sdl(sdl_event->key.keysym.sym);
    event->values[1].s32 = get_key_mod_from_sdl(sdl_event->key.keysym.mod);
    event->values[2].s32 = get_key_mod_from_sdl(sdl_event->key.keysym.scancode);
    return event;
  }

  if (sdl_event->type == SDL_MOUSEBUTTONDOWN ||
      sdl_event->type == SDL_MOUSEBUTTONUP) {
    sid_event* event = event_generate_event();
    event->type = sdl_event->type == SDL_MOUSEBUTTONDOWN
                      ? SID_EVENT_TYPE_MOUSE_DOWN
                      : SID_EVENT_TYPE_MOUSE_UP;
    event->values[0].s32 = get_mouse_button_from_sdl(sdl_event->button.button);
    event->values[1].b8 =
        sdl_event->button.clicks > 1;  // Handle double clicks.
    return event;
  }

  if (sdl_event->type == SDL_CONTROLLERBUTTONDOWN ||
      sdl_event->type == SDL_CONTROLLERBUTTONUP) {
    sid_event* event = event_generate_event();
    event->type = sdl_event->type == SDL_CONTROLLERBUTTONDOWN
                      ? SID_EVENT_TYPE_GAMEPAD_DOWN
                      : SID_EVENT_TYPE_GAMEPAD_UP;
    event->values[0].s32 =
        get_gamepad_button_from_sdl(sdl_event->cbutton.button);
    event->values[1].s32 = get_gamepad_button_from_sdl(
        sdl_event->cbutton.which);  // Handle gamepad ID.
    return event;
  }

  if (sdl_event->type == SDL_MOUSEMOTION) {
    sid_event* event = event_generate_event();
    event->type = SID_EVENT_TYPE_MOUSE_MOVE;
    event->values[0].s32 = sdl_event->motion.x;
    event->values[1].s32 = sdl_event->motion.y;
    return event;
  }

  return SID_NULL;
}

void input_system_startup() {}

void input_system_shutdown() {}

void input_system_update() {
  SDL_Event sdl_event;

  while (SDL_PollEvent(&sdl_event) != 0) {
    sid_event* event = input_try_generate_event(&sdl_event);

    if (event == SID_NULL) {
      continue;
    }

    event_fire(event);
  }
}
