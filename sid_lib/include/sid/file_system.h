// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_FILE_SYSTEM_H_
#define SID_FILE_SYSTEM_H_

#include "sid_precompile.h"

typedef FILE sid_stream;

SID_EXPORT sid_stream* sid_open_file_readonly(const tchar* path);
SID_EXPORT sid_stream* sid_open_file_write(const tchar* path);
SID_EXPORT sid_stream* sid_open_file_binary_readonly(const tchar* path);
SID_EXPORT sid_stream* sid_open_file_binary_write(const tchar* path);
SID_EXPORT void sid_close_file(sid_stream* stream);
SID_EXPORT uindex sid_read_file(void* restrict buffer, uindex element_count,
                                sid_stream* restrict stream);
SID_EXPORT uindex sid_read_file_element(void* restrict buffer,
                                        sid_stream* restrict stream);
SID_EXPORT uindex sid_read_file_binary(void* restrict buffer,
                                       uindex element_size,
                                       uindex element_count,
                                       sid_stream* restrict stream);
SID_EXPORT uindex sid_read_file_element_binary(void* restrict buffer,
                                               uindex element_size,
                                               sid_stream* restrict stream);
SID_EXPORT uindex sid_write_file(const schar* buffer, uindex element_count,
                                 sid_stream* restrict stream);
SID_EXPORT uindex sid_write_file_element(const schar* buffer,
                                         sid_stream* restrict stream);
SID_EXPORT uindex sid_write_file_binary(const void* buffer, uindex element_size,
                                        uindex element_count,
                                        sid_stream* restrict stream);
SID_EXPORT uindex sid_write_file_element_binary(const void* buffer,
                                                uindex element_size,
                                                sid_stream* restrict stream);

#endif  // SID_FILE_SYSTEM_H_
