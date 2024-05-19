// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/hashmap.h"

#include "sid/hash.h"

static u64 sid_hash_key(const sid_fixed_hash_table* table,
                        sid_hashtable_key key, uindex entry_count) {
  SID_ASSERT(table != SID_NULL, "Table provided is null!");
  // TODO(m4jr0): Improve hash function.
  u64 hash = 0;

  switch (table->key_type) {
    case SID_HASHTABLE_KEY_TYPE_STRING:
      hash = sid_hash_crc32_str(key.str.key);
      break;
    case SID_HASHTABLE_KEY_TYPE_BYTES:
      hash = sid_hash_crc32(key.bytes.bytes, key.bytes.size);
      break;
    default:
      SID_ASSERT(false, "Hashtable has invalid key type!");
      break;
  }

  return hash % entry_count;
}

SID_EXPORT void sid_fixed_hashtable_generate(
    sid_hashtable_key_type key_type, uindex entry_size, u16 entry_alignment,
    uindex entry_count, sid_memory_tag tag, sid_fixed_hash_table* out_table) {
  SID_ASSERT(out_table != SID_NULL, "Table provided is null!");
  out_table->key_type = key_type;

  // TODO(m4jr0): Give the option to use a custom allocator.
  out_table->data =
      sid_allocate_aligned(entry_size * entry_count, entry_alignment, tag);
  out_table->entry_count = entry_count;
  out_table->entry_size = entry_size;

  sid_zero_memory(out_table->data,
                  out_table->entry_count * out_table->entry_size);
}

SID_EXPORT void sid_fixed_hashtable_generate_string(
    uindex entry_size, u16 entry_alignment, uindex entry_count,
    sid_memory_tag tag, sid_fixed_hash_table* out_table) {
  sid_fixed_hashtable_generate(SID_HASHTABLE_KEY_TYPE_STRING, entry_size,
                               entry_alignment, entry_count, tag, out_table);
}

SID_EXPORT void sid_fixed_hashtable_generate_bytes(
    uindex entry_size, u16 entry_alignment, uindex entry_count,
    sid_memory_tag tag, sid_fixed_hash_table* out_table) {
  sid_fixed_hashtable_generate(SID_HASHTABLE_KEY_TYPE_BYTES, entry_size,
                               entry_alignment, entry_count, tag, out_table);
}

SID_EXPORT void sid_fixed_hashtable_destroy(sid_fixed_hash_table* table,
                                            sid_memory_tag tag) {
  SID_ASSERT(table != SID_NULL, "Data of table provided is null!");
  sid_free(table->data, tag);
  table->data = SID_NULL;
  table->entry_count = 0;
  table->entry_size = 0;
}

SID_EXPORT void sid_fixed_hashtable_set(sid_fixed_hash_table* table,
                                        sid_hashtable_key key,
                                        const void* value) {
  SID_ASSERT(table != SID_NULL, "Table provided is null!");
  SID_ASSERT(value != SID_NULL, "Value provided is null!");
  u64 hash = sid_hash_key(table, key, table->entry_count);
  sid_copy_memory((u8*)table->data + (table->entry_size * hash), value,
                  table->entry_size);
}

SID_EXPORT void sid_fixed_hashtable_unset(sid_fixed_hash_table* table,
                                          sid_hashtable_key key) {
  SID_ASSERT(table != SID_NULL, "Table provided is null!");
  u64 hash = sid_hash_key(table, key, table->entry_count);
  sid_zero_memory((u8*)table->data + (table->entry_size * hash),
                  table->entry_size);
}

SID_EXPORT void sid_fixed_hashtable_get(sid_fixed_hash_table* table,
                                        sid_hashtable_key key,
                                        void** out_value) {
  SID_ASSERT(table != SID_NULL, "Table provided is null!");
  SID_ASSERT(out_value != SID_NULL, "Out value provided is null!");
  u64 hash = sid_hash_key(table, key, table->entry_count);
  sid_copy_memory(*out_value, (u8*)table->data + (table->entry_size * hash),
                  table->entry_size);
}

SID_EXPORT void* sid_fixed_hashtable_get_ref(sid_fixed_hash_table* table,
                                             sid_hashtable_key key) {
  SID_ASSERT(table != SID_NULL, "Table provided is null!");
  u64 hash = sid_hash_key(table, key, table->entry_count);
  return (void*)((u8*)table->data + (table->entry_size * hash));
}

SID_EXPORT void sid_fixed_hashtable_fill(sid_fixed_hash_table* table,
                                         const void* data, uindex data_size) {
  SID_ASSERT(table != SID_NULL, "Table provided is null!");
  SID_ASSERT(data != SID_NULL, "Data provided is null!");
  SID_ASSERT(data_size != 0, "Data size provided is 0!");
  uindex table_entry_size = table->entry_size;
  SID_ASSERT(data_size <= table_entry_size, "Data size provided is too big!");
  u8* table_data = table->data;
  uindex table_entry_count = table->entry_count;
  uptr table_end = (uptr)table_data + table_entry_count * table_entry_size;

  while ((uptr)table_data < table_end) {
    sid_copy_memory(table_data, data, data_size);
    table_data += table_entry_size;
  }
}
