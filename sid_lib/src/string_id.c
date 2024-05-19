// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/string_id.h"

#include "sid/hash.h"
#include "sid/memory.h"
#include "sid/string.h"

SID_EXPORT sid_string_id sid_generate_string_id(const schar* str) {
  SID_ASSERT(str != SID_NULL, "String provided is null!");
  return sid_hash_crc32_str(str);
}

SID_EXPORT sid_string_id
sid_generate_namespaced_string_id(const schar* namespace, const schar* str) {
  SID_ASSERT(namespace != SID_NULL, "Namespace provided is null!");
  SID_ASSERT(str != SID_NULL, "String provided is null!");
  uindex namespace_length = sid_str_len(namespace);
  uindex str_length = sid_str_len(str);
  uindex total_length = namespace_length + str_length + 1;

  schar* tmp = sid_allocate_tmp(total_length + 1, alignof(schar));
  sid_copy_memory(tmp, namespace, namespace_length);
  tmp[namespace_length] = '/';
  sid_copy_memory(tmp + namespace_length + 1, str, str_length * sizeof(schar));
  tmp[total_length] = '\0';
  sid_string_id string_id = sid_generate_string_id(tmp);
  sid_free_tmp(tmp);
  return string_id;
}

SID_EXPORT sid_string_id sid_generate_string_id_from_tchar(const tchar* str) {
  SID_ASSERT(str != SID_NULL, "String provided is null!");
  return sid_hash_crc32_tstr(str);
}

SID_EXPORT sid_string_id sid_generate_namespaced_string_id_from_tchar(
    const schar* namespace, const tchar* str) {
  SID_ASSERT(namespace != SID_NULL, "Namespace provided is null!");
  SID_ASSERT(str != SID_NULL, "String provided is null!");
  uindex namespace_length = sid_str_len(namespace);
  uindex str_length = sid_tstr_len(str);
  uindex total_length = namespace_length + str_length + 1;
  tchar* tmp =
      sid_allocate_tmp((total_length + 1) * sizeof(tchar), alignof(tchar));
  sid_str_convert_tstr_secure(tmp, namespace, namespace_length);
  tmp[namespace_length] = SID_TCHAR('/');
  sid_copy_memory(tmp + namespace_length + 1, str, str_length * sizeof(tchar));
  tmp[total_length] = SID_TCHAR('\0');
  sid_string_id string_id = sid_hash_crc32_tstr(tmp);
  sid_free_tmp(tmp);
  return string_id;
}