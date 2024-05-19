// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/resource.h"

#include "sid/file_system.h"

SID_EXPORT void sid_read_sprite_sheet_resource(
    const tchar* path, sid_sprite_sheet_resource* resource) {
  sid_stream* stream = sid_open_file_binary_readonly(path);

  sid_read_file_element_binary(&resource->id, sizeof(sid_sprite_sheet_id),
                               stream);
  sid_read_file_element_binary(&resource->width, sizeof(sid_sprite_sheet_dim),
                               stream);
  sid_read_file_element_binary(&resource->height, sizeof(sid_sprite_sheet_dim),
                               stream);
  sid_read_file_element_binary(&resource->channel_count, sizeof(u8), stream);
  sid_read_file_element_binary(&resource->format, sizeof(sid_texture_format),
                               stream);
  sid_read_file_element_binary(&resource->size, sizeof(uindex), stream);

  // TODO(m4jr0): Use custom allocator.
  resource->data = sid_allocate(resource->size, SID_MEMORY_TAG_RESOURCE);
  sid_read_file_element_binary(resource->data, resource->size, stream);

  sid_close_file(stream);
}

SID_EXPORT void sid_read_animation_def_resource(
    const tchar* path, sid_animation_def_resource* resource) {
  sid_stream* stream = sid_open_file_binary_readonly(path);

  sid_read_file_element_binary(&resource->id, sizeof(sid_animation_def_id),
                               stream);
  sid_read_file_element_binary(&resource->sheet_id, sizeof(sid_sprite_sheet_id),
                               stream);
  sid_read_file_element_binary(&resource->frame_count,
                               sizeof(sid_animation_frame_index), stream);

  for (sid_animation_frame_index i = 0;
       i < resource->frame_count && i < SID_MAX_ANIMATION_FRAME_COUNT; ++i) {
    sid_read_file_element_binary(&resource->frames[i].pos.x,
                                 sizeof(sid_animation_frame_coord), stream);
    sid_read_file_element_binary(&resource->frames[i].pos.y,
                                 sizeof(sid_animation_frame_coord), stream);
    sid_read_file_element_binary(&resource->frames[i].dims.width,
                                 sizeof(sid_animation_frame_dim), stream);
    sid_read_file_element_binary(&resource->frames[i].dims.height,
                                 sizeof(sid_animation_frame_dim), stream);
    sid_read_file_element_binary(&resource->frames[i].duration,
                                 sizeof(sid_animation_frame_duration), stream);
  }

  sid_close_file(stream);
}

SID_EXPORT void sid_read_animation_resource(const tchar* path,
                                            sid_animation_resource* resource) {
  sid_stream* stream = sid_open_file_binary_readonly(path);

  sid_read_file_element_binary(&resource->id, sizeof(sid_animation_id), stream);
  sid_read_file_element_binary(&resource->def_id, sizeof(sid_animation_def_id),
                               stream);
  sid_read_file_element_binary(&resource->offset,
                               sizeof(sid_animation_frame_index), stream);
  sid_read_file_element_binary(&resource->length,
                               sizeof(sid_animation_frame_index), stream);

  sid_close_file(stream);
}