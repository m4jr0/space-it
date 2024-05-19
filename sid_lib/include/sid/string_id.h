// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_LIB_STRING_ID_H_
#define SID_LIB_STRING_ID_H_

#include "sid_precompile.h"

typedef u32 sid_string_id;

SID_EXPORT sid_string_id sid_generate_string_id(const schar* str);
SID_EXPORT sid_string_id
sid_generate_namespaced_string_id(const schar* namespace, const schar* str);
SID_EXPORT sid_string_id sid_generate_string_id_from_tchar(const tchar* str);
SID_EXPORT sid_string_id sid_generate_namespaced_string_id_from_tchar(
    const schar* namespace, const tchar* str);

#define SID_STRING_ID(str) sid_generate_string_id(str)
#define SID_NAMESPACED_STRING_ID(namespace, str) \
  sid_generate_namespaced_string_id(namespace, str)
#define SID_STRING_ID_FORMAT "%u"

#endif  // SID_LIB_STRING_ID_H_