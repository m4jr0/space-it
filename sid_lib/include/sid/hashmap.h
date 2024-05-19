// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_LIB_HASHMAP_H_
#define SID_LIB_HASHMAP_H_

#include "sid_precompile.h"

#include "sid/string_id.h"

typedef enum sid_hashtable_key_type {
  SID_HASHTABLE_UNKNOWN = 0,
  SID_HASHTABLE_KEY_TYPE_STRING,
  SID_HASHTABLE_KEY_TYPE_BYTES,
} sid_hashtable_key_type;

typedef struct sid_hashtable_key {
  sid_hashtable_key_type key_type;
  union {
    struct {
      const schar* key;
    } str;
    struct {
      const void* bytes;
      uindex size;
    } bytes;
  };
} sid_hashtable_key;

#define SID_HASHTABLE_STRING_KEY(str_key)                         \
  ((sid_hashtable_key){.key_type = SID_HASHTABLE_KEY_TYPE_STRING, \
                       .str = {.key = str_key}})

#define SID_HASHTABLE_BYTES_KEY(bytes_key, key_size)             \
  ((sid_hashtable_key){.key_type = SID_HASHTABLE_KEY_TYPE_BYTES, \
                       .bytes = {.bytes = bytes_key, .size = key_size}})

#define SID_HASHTABLE_STRING_ID_KEY(string_id) \
  SID_HASHTABLE_BYTES_KEY(&string_id, sizeof(sid_string_id))

typedef struct sid_fixed_hash_table {
  sid_hashtable_key_type key_type;
  uindex entry_size;
  uindex entry_count;
  void* data;
} sid_fixed_hash_table;

SID_EXPORT void sid_fixed_hashtable_generate(
    sid_hashtable_key_type key_type, uindex entry_size, u16 entry_alignment,
    uindex entry_count, sid_memory_tag tag, sid_fixed_hash_table* out_table);
SID_EXPORT void sid_fixed_hashtable_generate_string(
    uindex entry_size, u16 entry_alignment, uindex entry_count,
    sid_memory_tag tag, sid_fixed_hash_table* out_table);
SID_EXPORT void sid_fixed_hashtable_generate_bytes(
    uindex entry_size, u16 entry_alignment, uindex entry_count,
    sid_memory_tag tag, sid_fixed_hash_table* out_table);
SID_EXPORT void sid_fixed_hashtable_destroy(sid_fixed_hash_table* table,
                                            sid_memory_tag tag);
SID_EXPORT void sid_fixed_hashtable_set(sid_fixed_hash_table* table,
                                        sid_hashtable_key key,
                                        const void* value);
SID_EXPORT void sid_fixed_hashtable_unset(sid_fixed_hash_table* table,
                                          sid_hashtable_key key);
SID_EXPORT void sid_fixed_hashtable_get(sid_fixed_hash_table* table,
                                        sid_hashtable_key key,
                                        void** out_value);
SID_EXPORT void* sid_fixed_hashtable_get_ref(sid_fixed_hash_table* table,
                                             sid_hashtable_key key);
SID_EXPORT void sid_fixed_hashtable_fill(sid_fixed_hash_table* table,
                                         const void* data, uindex data_size);

#endif  // SID_LIB_HASHMAP_H_
