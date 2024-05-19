// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "rendering_system.h"

#include "SDL2/SDL.h"

#include "config.h"
#include "system/input_system.h"
#include "system/resource_system.h"

#define SID_MAX_SPRITE_SHEET_COUNT 64
#define SID_MAX_SPRITE_COUNT 64

typedef struct rendering_context {
  b8 initialized;
  sid_color clear_color;
  sid_fixed_hash_table sprite_sheets;
  void* driver;
} rendering_context;

static rendering_context context;

typedef struct sdl_driver {
  SDL_Window* window;
  SDL_Renderer* renderer;
} sdl_driver;

static void rendering_invalidate_sprite_sheet(sid_sprite_sheet* sheet) {
  sheet->id = SID_INVALID_SPRITE_SHEET_ID;
  sheet->texture.size = 0;
  sheet->width = 0;
  sheet->height = 0;

  if (sheet->texture.data != SID_NULL) {
    SDL_DestroyTexture(sheet->texture.data);
    sheet->texture.data = SID_NULL;
  }
}

static void rendering_startup_sdl() {
  context.driver = sid_allocate_aligned(sizeof(sdl_driver), alignof(sdl_driver),
                                        SID_MEMORY_TAG_RENDERING);
  sdl_driver* driver = (sdl_driver*)context.driver;
  driver->renderer = SID_NULL;
  driver->window = SID_NULL;

#ifdef SID_DEBUG
  s32 result =
#endif  // SID_DEBUG
      SDL_Init(SDL_INIT_VIDEO);

#ifdef SID_DEBUG
  SID_ASSERT(result == 0,
             "An error occurred while initializing the SDL library: %s",
             SDL_GetError());
#endif  // SID_DEBUG

  context.initialized = SID_TRUE;
  context.clear_color.r = config_u8_get(SID_CONFIG_CLEAR_COLOR_R);
  context.clear_color.g = config_u8_get(SID_CONFIG_CLEAR_COLOR_G);
  context.clear_color.b = config_u8_get(SID_CONFIG_CLEAR_COLOR_B);
  context.clear_color.a = 255;

  driver->window = SDL_CreateWindow(
      config_str_get(SID_CONFIG_GAME_TITLE), SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, config_u16_get(SID_CONFIG_WINDOW_WIDTH),
      config_u16_get(SID_CONFIG_WINDOW_HEIGHT), SDL_WINDOW_SHOWN);

  SID_ASSERT(driver->window != SID_NULL,
             "An error occurred while creating the window: %s", SDL_GetError());

  // TODO(m4jr0): Support other configurations (SDL_RENDERER_PRESENTVSYNC,
  // etc.).
  driver->renderer =
      SDL_CreateRenderer(driver->window, -1, SDL_RENDERER_ACCELERATED);

  SID_ASSERT(driver->renderer != SID_NULL,
             "An error occurred while creating the renderer: %s",
             SDL_GetError());
}

static void rendering_shutdown_sdl() {
  if (context.driver == SID_NULL) {
    return;
  }

  sdl_driver* driver = (sdl_driver*)context.driver;

  if (driver->renderer != SID_NULL) {
    SDL_DestroyRenderer(driver->renderer);
    driver->renderer = SID_NULL;
  }

  if (driver->window != SID_NULL) {
    SDL_DestroyWindow(driver->window);
    driver->window = SID_NULL;
  }

  if (context.initialized == SID_TRUE) {
    SDL_Quit();
  }

  sid_free(context.driver, SID_MEMORY_TAG_RENDERING);
  context.driver = SID_NULL;
  context.initialized = SID_FALSE;
}

void rendering_system_startup() {
  rendering_startup_sdl();

  sid_fixed_hashtable_generate_bytes(
      sizeof(sid_sprite_sheet), alignof(sid_sprite_sheet),
      SID_MAX_SPRITE_SHEET_COUNT, SID_MEMORY_TAG_RENDERING,
      &context.sprite_sheets);

  {
    sid_sprite_sheet invalid_sheet = {0};
    rendering_invalidate_sprite_sheet(&invalid_sheet);
    sid_fixed_hashtable_fill(&context.sprite_sheets, &invalid_sheet,
                             sizeof(sid_sprite_sheet));
  }
}

void rendering_system_shutdown() { rendering_shutdown_sdl(); }

void draw_sprite(const sid_animator* animator, f64 interpolation) {
  // TODO(m4jr0): Take interpolation into account.
  (void)interpolation;
  const sid_animation_frame* frame = sid_get_animation_frame(animator);

  // TODO(m4jr0): Use non-hardcoded zoom factor.
  f32 zoom_factor = 3.0f;
  SDL_Rect src_rect = {frame->pos.x, frame->pos.y, frame->dims.width,
                       frame->dims.height};

  SDL_Rect dst_rect = {animator->position.x, animator->position.y,
                       (s32)(frame->dims.width * zoom_factor),
                       (s32)(frame->dims.height * zoom_factor)};

  sdl_driver* driver = (sdl_driver*)context.driver;
  SDL_RenderCopy(driver->renderer,
                 (SDL_Texture*)animator->def->sheet->texture.data, &src_rect,
                 &dst_rect);
}

void rendering_system_update(const rendering_frame* frame) {
  sdl_driver* driver = (sdl_driver*)context.driver;

  SDL_SetRenderDrawColor(driver->renderer, context.clear_color.r,
                         context.clear_color.g, context.clear_color.b,
                         context.clear_color.a);
  SDL_RenderClear(driver->renderer);

  const sid_animator* const* animator_cursor = frame->animators;
  const sid_animator* const* animator_end =
      animator_cursor + frame->animator_count;

  while (animator_cursor != animator_end) {
    draw_sprite(*animator_cursor, frame->interpolation);
    ++animator_cursor;
  }

  SDL_RenderPresent(driver->renderer);
  input_system_update();
}

const sid_sprite_sheet* rendering_load_sprite_sheet(sid_sprite_sheet_id id) {
  sid_sprite_sheet* sheet = sid_fixed_hashtable_get_ref(
      &context.sprite_sheets, SID_HASHTABLE_STRING_ID_KEY(id));

  if (sheet->id != SID_INVALID_SPRITE_SHEET_ID) {
    return sheet;
  }

  const sid_sprite_sheet_resource* resource = resource_get_sprite_sheet(id);

  SID_ASSERT(resource != SID_NULL, "Resource provided is null!");
  sdl_driver* driver = (sdl_driver*)context.driver;

  s32 pitch = resource->width * resource->channel_count;
  pitch = (s32)sid_align_address(pitch, 4);

#if SDL_BYTEORDER == SDL_LIL_ENDIAN
  u32 r_mask = 0x000000ff;
  u32 g_mask = 0x0000ff00;
  u32 b_mask = 0x00ff0000;
  u32 a_mask = (resource->channel_count == 4) ? 0xff000000 : 0x0;
#else
  u32 s = (resource->channel_count == 4) ? 0x0 : 8;
  u32 r_mask = 0xff000000 >> s;
  u32 g_mask = 0x00ff0000 >> s;
  u32 b_mask = 0x0000ff00 >> s;
  u32 a_mask = 0x000000ff >> s;
#endif  // SDL_BYTEORDER == SDL_LIL_ENDIAN

  SDL_Surface* sdl_surface = SDL_CreateRGBSurfaceFrom(
      resource->data, (s32)resource->width, (s32)resource->height,
      (s32)resource->channel_count * 8, pitch, r_mask, g_mask, b_mask, a_mask);

  SID_ASSERT(sdl_surface != SID_NULL, "Unable to create RGB surface: %s",
             SDL_GetError());

  SDL_Texture* sdl_texture =
      SDL_CreateTextureFromSurface(driver->renderer, sdl_surface);

  SDL_FreeSurface(sdl_surface);

  SID_ASSERT(sdl_texture != SID_NULL,
             "Unable to create texture from surface: %s", SDL_GetError());

  sheet->id = resource->id;
  sheet->width = resource->width;
  sheet->height = resource->height;
  sheet->texture.data = sdl_texture;
  sheet->texture.size = resource->size;

  return sheet;
}

void rendering_unload_sprite_sheet(sid_sprite_sheet_id id) {
  sid_sprite_sheet* sheet = sid_fixed_hashtable_get_ref(
      &context.sprite_sheets, SID_HASHTABLE_STRING_ID_KEY(id));

  if (sheet->id != SID_INVALID_SPRITE_SHEET_ID) {
    return;
  }

  rendering_invalidate_sprite_sheet(sheet);
}

const sid_sprite_sheet* rendering_get_sprite_sheet(sid_sprite_sheet_id id) {
  sid_sprite_sheet* sheet = sid_fixed_hashtable_get_ref(
      &context.sprite_sheets, SID_HASHTABLE_STRING_ID_KEY(id));

  SID_ASSERT(sheet->id != SID_INVALID_SPRITE_SHEET_ID,
             "Tried to retrieve sprite sheet " SID_STRING_ID_FORMAT
             ", but it is not loaded!",
             id);

  return sheet;
}