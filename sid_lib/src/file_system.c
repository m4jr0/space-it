// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/file_system.h"

SID_EXPORT sid_stream* sid_open_file_readonly(const tchar* path) {
#ifdef SID_WIDE_TCHAR
  sid_stream* stream = _wfopen(path, L"r");
#else
  sid_stream* stream = fopen(path, "r");
#endif  // SID_WIDE_TCHAR

  SID_ASSERT(stream != SID_NULL,
             "Error opening file at path " SID_TCHAR_FORMAT ": %s", path,
             strerror(errno));

  return stream;
}

SID_EXPORT sid_stream* sid_open_file_write(const tchar* path) {
#ifdef SID_WIDE_TCHAR
  sid_stream* stream = _wfopen(path, L"w");
#else
  sid_stream* stream = fopen(path, "w");
#endif  // SID_WIDE_TCHAR

  SID_ASSERT(stream != SID_NULL,
             "Error opening file at path " SID_TCHAR_FORMAT ": %s", path,
             strerror(errno));

  return stream;
}

SID_EXPORT sid_stream* sid_open_file_binary_readonly(const tchar* path) {
#ifdef SID_WIDE_TCHAR
  sid_stream* stream = _wfopen(path, L"rb");
#else
  sid_stream* stream = fopen(path, "rb");
#endif  // SID_WIDE_TCHAR

  SID_ASSERT(stream != SID_NULL,
             "Error opening file at path " SID_TCHAR_FORMAT ": %s", path,
             strerror(errno));

  return stream;
}

SID_EXPORT sid_stream* sid_open_file_binary_write(const tchar* path) {
#ifdef SID_WIDE_TCHAR
  sid_stream* stream = _wfopen(path, L"wb");
#else
  sid_stream* stream = fopen(path, "wb");
#endif  // SID_WIDE_TCHAR

  SID_ASSERT(stream != SID_NULL,
             "Error opening file at path " SID_TCHAR_FORMAT ": %s", path,
             strerror(errno));

  return stream;
}

SID_EXPORT void sid_close_file(sid_stream* stream) { fclose(stream); }

SID_EXPORT uindex sid_read_file(void* restrict buffer, uindex element_count,
                                sid_stream* restrict stream) {
  return fread(buffer, sizeof(schar), element_count, stream);
}

SID_EXPORT uindex sid_read_file_element(void* restrict buffer,
                                        sid_stream* restrict stream) {
  return sid_read_file_binary(buffer, sizeof(schar), 1, stream);
}

SID_EXPORT uindex sid_read_file_binary(void* restrict buffer,
                                       uindex element_size,
                                       uindex element_count,
                                       sid_stream* restrict stream) {
  return fread(buffer, element_size, element_count, stream);
}

SID_EXPORT uindex sid_read_file_element_binary(void* restrict buffer,
                                               uindex element_size,
                                               sid_stream* restrict stream) {
  return sid_read_file_binary(buffer, element_size, 1, stream);
}

SID_EXPORT uindex sid_write_file(const schar* buffer, uindex element_count,
                                 sid_stream* restrict stream) {
  return fwrite(buffer, sizeof(schar), element_count, stream);
}

SID_EXPORT uindex sid_write_file_element(const schar* buffer,
                                         sid_stream* restrict stream) {
  return sid_write_file_binary(buffer, sizeof(schar), 1, stream);
}

SID_EXPORT uindex sid_write_file_binary(const void* buffer, uindex element_size,
                                        uindex element_count,
                                        sid_stream* restrict stream) {
  return fwrite(buffer, element_size, element_count, stream);
}

SID_EXPORT uindex sid_write_file_element_binary(const void* buffer,
                                                uindex element_size,
                                                sid_stream* restrict stream) {
  return sid_write_file_binary(buffer, element_size, 1, stream);
}