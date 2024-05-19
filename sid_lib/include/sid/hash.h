// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_HASH_H_
#define SID_HASH_H_

#include "sid_precompile.h"

SID_EXPORT u32 sid_hash_crc32(const void* data, uindex length);
SID_EXPORT u32 sid_hash_crc32_str(const schar* str);
SID_EXPORT u32 sid_hash_crc32_wstr(const wchar* str);
SID_EXPORT u32 sid_hash_crc32_tstr(const tchar* str);

#endif  // SID_HASH_H_
