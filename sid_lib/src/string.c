// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#include "sid/string.h"

#include "sid/define.h"

#define SID_WSTR_MAX_UNSECURE_BUFFER_COUNT 256

SID_EXPORT s32 sid_str_compare(const schar* str1, const schar* str2) {
  return strcmp(str1, str2);
}

SID_EXPORT s32 sid_wstr_compare(const wchar* str1, const wchar* str2) {
  return wcscmp(str1, str2);
}

SID_EXPORT s32 sid_tstr_compare(const tchar* str1, const tchar* str2) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_compare(str1, str2);
#else
  return sid_str_compare(str1, str2);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT s32 sid_str_compare_secure(const schar* str1, const schar* str2,
                                      uindex length) {
  return strncmp(str1, str2, length);
}

SID_EXPORT s32 sid_wstr_compare_secure(const wchar* str1, const wchar* str2,
                                       uindex length) {
  return wcsncmp(str1, str2, length);
}

SID_EXPORT s32 sid_tstr_compare_secure(const tchar* str1, const tchar* str2,
                                       uindex length) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_compare_secure(str1, str2, length);
#else
  return sid_str_compare_secure(str1, str2, length);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT b8 sid_str_equal(const schar* str1, const schar* str2) {
  if (str1 == SID_NULL && str2 == SID_NULL) {
    return SID_TRUE;
  }

  if (str1 == SID_NULL || str2 == SID_NULL) {
    return SID_FALSE;
  }

  return sid_str_compare(str1, str2) == 0;
}

SID_EXPORT b8 sid_wstr_equal(const wchar* str1, const wchar* str2) {
  if (str1 == SID_NULL && str2 == SID_NULL) {
    return SID_TRUE;
  }

  if (str1 == SID_NULL || str2 == SID_NULL) {
    return SID_FALSE;
  }

  return sid_wstr_compare(str1, str2) == 0;
}

SID_EXPORT b8 sid_tstr_equal(const tchar* str1, const tchar* str2) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_equal(str1, str2);
#else
  return sid_str_equal(str1, str2);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT b8 sid_str_equal_secure(const schar* str1, uindex str1_len,
                                   const schar* str2, uindex str2_len) {
  if (str1_len != str2_len) {
    return SID_FALSE;
  }

  if (str1 == SID_NULL && str2 == SID_NULL) {
    return SID_TRUE;
  }

  if (str1 == SID_NULL || str2 == SID_NULL) {
    return SID_FALSE;
  }

  return sid_str_compare_secure(str1, str2, str1_len) == 0;
}

SID_EXPORT b8 sid_wstr_equal_secure(const wchar* str1, uindex str1_len,
                                    const wchar* str2, uindex str2_len) {
  if (str1_len != str2_len) {
    return SID_FALSE;
  }

  if (str1 == SID_NULL && str2 == SID_NULL) {
    return SID_TRUE;
  }

  if (str1 == SID_NULL || str2 == SID_NULL) {
    return SID_FALSE;
  }

  return sid_wstr_compare_secure(str1, str2, str1_len) == 0;
}

SID_EXPORT b8 sid_tstr_equal_secure(const tchar* str1, uindex str1_len,
                                    const tchar* str2, uindex str2_len) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_equal_secure(str1, str1_len, str2, str2_len);
#else
  return sid_str_equal_secure(str1, str1_len, str2, str2_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT s32 sid_str_compare_insensitive(const schar* str1,
                                           const schar* str2) {
#ifdef SID_GCC
  return strcasecmp(str1, str2);
#elif defined(SID_MSVC)
  return _stricmp(str1, str2);
#endif  // SID_GCC
}

SID_EXPORT s32 sid_wstr_compare_insensitive(const wchar* str1,
                                            const wchar* str2) {
#ifdef SID_GCC
  return wcscasecmp(str1, str2);
#elif defined(SID_MSVC)
  return _wcsicmp(str1, str2);
#endif  // SID_GCC
}

SID_EXPORT s32 sid_tstr_compare_insensitive(const tchar* str1,
                                            const tchar* str2) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_compare_insensitive(str1, str2);
#else
  return sid_str_compare_insensitive(str1, str2);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT s32 sid_str_compare_insensitive_secure(const schar* str1,
                                                  const schar* str2,
                                                  uindex length) {
#ifdef SID_GCC
  return strncasecmp(str1, str2, length);
#elif defined(SID_MSVC)
  return _strnicmp(str1, str2, length);
#endif  // SID_GCC
}

SID_EXPORT s32 sid_wstr_compare_insensitive_secure(const wchar* str1,
                                                   const wchar* str2,
                                                   uindex length) {
#ifdef SID_GCC
  return wcsncasecmp(str1, str2, length);
#elif defined(SID_MSVC)
  return _wcsnicmp(str1, str2, length);
#endif  // SID_GCC
}

SID_EXPORT s32 sid_tstr_compare_insensitive_secure(const tchar* str1,
                                                   const tchar* str2,
                                                   uindex length) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_compare_insensitive_secure(str1, str2, length);
#else
  return sid_str_compare_insensitive_secure(str1, str2, length);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT b8 sid_str_equal_insensitive(const schar* str1, const schar* str2) {
  if (str1 == SID_NULL && str2 == SID_NULL) {
    return SID_TRUE;
  }

  if (str1 == SID_NULL || str2 == SID_NULL) {
    return SID_FALSE;
  }

  return sid_str_compare_insensitive(str1, str2) == 0;
}

SID_EXPORT b8 sid_wstr_equal_insensitive(const wchar* str1, const wchar* str2) {
  if (str1 == SID_NULL && str2 == SID_NULL) {
    return SID_TRUE;
  }

  if (str1 == SID_NULL || str2 == SID_NULL) {
    return SID_FALSE;
  }

  return sid_wstr_compare_insensitive(str1, str2) == 0;
}

SID_EXPORT b8 sid_tstr_equal_insensitive(const tchar* str1, const tchar* str2) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_equal_insensitive(str1, str2);
#else
  return sid_str_equal_insensitive(str1, str2);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT b8 sid_str_equal_insensitive_secure(const schar* str1,
                                               uindex str1_len,
                                               const schar* str2,
                                               uindex str2_len) {
  if (str1_len != str2_len) {
    return SID_FALSE;
  }

  if (str1 == SID_NULL && str2 == SID_NULL) {
    return SID_TRUE;
  }

  if (str1 == SID_NULL || str2 == SID_NULL) {
    return SID_FALSE;
  }

  return sid_str_compare_insensitive_secure(str1, str2, str1_len) == 0;
}

SID_EXPORT b8 sid_wstr_equal_insensitive_secure(const wchar* str1,
                                                uindex str1_len,
                                                const wchar* str2,
                                                uindex str2_len) {
  if (str1_len != str2_len) {
    return SID_FALSE;
  }

  if (str1 == SID_NULL && str2 == SID_NULL) {
    return SID_TRUE;
  }

  if (str1 == SID_NULL || str2 == SID_NULL) {
    return SID_FALSE;
  }

  return sid_wstr_compare_insensitive_secure(str1, str2, str1_len) == 0;
}

SID_EXPORT b8 sid_tstr_equal_insensitive_secure(const tchar* str1,
                                                uindex str1_len,
                                                const tchar* str2,
                                                uindex str2_len) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_equal_insensitive_secure(str1, str1_len, str2, str2_len);
#else
  return sid_str_equal_insensitive_secure(str1, str1_len, str2, str2_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT b8 sid_schar_space(schar c) { return (b8)isspace(c); }

SID_EXPORT b8 sid_wchar_space(wchar c) { return (b8)iswspace(c); }

SID_EXPORT b8 sid_tchar_space(tchar c) {
#ifdef SID_WIDE_TCHAR
  return sid_wchar_space(c);
#else
  return sid_schar_space(c);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT b8 sid_schar_alpha(schar c) { return (b8)isalpha(c); }

SID_EXPORT b8 sid_wchar_alpha(wchar c) { return (b8)iswalpha(c); }

SID_EXPORT b8 sid_tchar_alpha(tchar c) {
#ifdef SID_WIDE_TCHAR
  return sid_wchar_alpha(c);
#else
  return sid_schar_alpha(c);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_str_copy(schar* dst, const schar* src) {
  return sid_str_copy_offset(dst, src, 0, 0);
}

SID_EXPORT wchar* sid_wstr_copy(wchar* dst, const wchar* src) {
  return sid_wstr_copy_offset(dst, src, 0, 0);
}

SID_EXPORT tchar* sid_tstr_copy(tchar* dst, const tchar* src) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy(dst, src);
#else
  return sid_str_copy(dst, src);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_str_copy_secure(schar* dst, const schar* src,
                                      uindex length) {
  return sid_str_copy_offset_secure(dst, src, length, 0, 0);
}

SID_EXPORT wchar* sid_wstr_copy_secure(wchar* dst, const wchar* src,
                                       uindex length) {
  return sid_wstr_copy_offset_secure(dst, src, length, 0, 0);
}

SID_EXPORT tchar* sid_tstr_copy_secure(tchar* dst, const tchar* src,
                                       uindex length) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy_secure(dst, src, length);
#else
  return sid_str_copy_secure(dst, src, length);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_str_copy_offset(schar* dst, const schar* src,
                                      uindex dst_offset, uindex src_offset) {
#ifdef SID_WINDOWS
#ifdef SID_DEBUG
  error_code result =
#endif  // SID_DEBUG
      strcpy_s(dst + dst_offset, sid_str_len_with_null(src), src + src_offset);

#ifdef SID_DEBUG
  SID_ASSERT(result == 0, "An error occurred while copying a string");
#endif  // SID_DEBUG
#else
  strcpy(dst + dst_offset, src + src_offset);
#endif  // SID_WINDOWS
  return dst;
}

SID_EXPORT wchar* sid_wstr_copy_offset(wchar* dst, const wchar* src,
                                       uindex dst_offset, uindex src_offset) {
#ifdef SID_WINDOWS
#ifdef SID_DEBUG
  error_code result =
#endif  // SID_DEBUG
      wcscpy_s(dst + dst_offset, sid_wstr_len_with_null(src), src + src_offset);

#ifdef SID_DEBUG
  SID_ASSERT(result == 0, "An error occurred while copying a string");
#endif  // SID_DEBUG
#else
  wcscpy(dst + dst_offset, src + src_offset);
#endif  // SID_WINDOWS
  return dst;
}

SID_EXPORT tchar* sid_tstr_copy_offset(tchar* dst, const tchar* src,
                                       uindex dst_offset, uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy_offset(dst, src, dst_offset, src_offset);
#else
  return sid_str_copy_offset(dst, src, dst_offset, src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_str_copy_offset_secure(schar* dst, const schar* src,
                                             uindex length, uindex dst_offset,
                                             uindex src_offset) {
  SID_ASSERT(src != SID_NULL, "Source string provided is null!");
  SID_ASSERT(dst != SID_NULL, "Destination string provided is null!");
#ifdef SID_MSVC
#ifdef SID_DEBUG
  error_code result =
#endif  // SID_DEBUG
      strncpy_s(dst + dst_offset, length + 1, src + src_offset, length);

#ifdef SID_DEBUG
  SID_ASSERT(result == 0, "An error occurred while copying a string");
#endif  // SID_DEBUG
#else
  return strncpy(dst + dst_offset, src + src_offset, length);
#endif  // SID_MSVC
  return dst;
}

SID_EXPORT wchar* sid_wstr_copy_offset_secure(wchar* dst, const wchar* src,
                                              uindex length, uindex dst_offset,
                                              uindex src_offset) {
  SID_ASSERT(src != SID_NULL, "Source string provided is null!");
  SID_ASSERT(dst != SID_NULL, "Destination string provided is null!");
#ifdef SID_MSVC
#ifdef SID_DEBUG
  error_code result =
#endif  // SID_DEBUG
      wcsncpy_s(dst + dst_offset, length + 1, src + src_offset, length);
#ifdef SID_DEBUG
  SID_ASSERT(result == 0, "An error occurred while copying a string");
#endif  // SID_DEBUG
#else
  wcsncpy(dst + dst_offset, src + src_offset, length);
#endif  // SID_MSVC
  return dst;
}

SID_EXPORT tchar* sid_tstr_copy_offset_secure(tchar* dst, const tchar* src,
                                              uindex length, uindex dst_offset,
                                              uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy_offset_secure(dst, src, length, dst_offset, src_offset);
#else
  return sid_str_copy_offset_secure(dst, src, length, dst_offset, src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT wchar* sid_str_convert_wstr(wchar* dst, const schar* src) {
  return sid_str_convert_wstr_offset(dst, src, 0, 0);
}

SID_EXPORT tchar* sid_str_convert_tstr(tchar* dst, const schar* src) {
#ifdef SID_WIDE_TCHAR
  return sid_str_convert_wstr(dst, src);
#else
  return sid_str_copy(dst, src);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_wstr_convert_str(schar* dst, const wchar* src) {
  return sid_wstr_convert_str_offset(dst, src, 0, 0);
}

SID_EXPORT tchar* sid_wstr_convert_tstr(tchar* dst, const wchar* src) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy(dst, src);
#else
  return sid_wstr_convert_str(dst, src);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_tstr_convert_str(schar* dst, const tchar* src) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_convert_str(dst, src);
#else
  return sid_str_copy(dst, src);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT wchar* sid_tstr_convert_wstr(wchar* dst, const tchar* src) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy(dst, src);
#else
  return sid_str_convert_wstr(dst, src);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT wchar* sid_str_convert_wstr_secure(wchar* dst, const schar* src,
                                              uindex length) {
  return sid_str_convert_wstr_offset_secure(dst, src, length, 0, 0);
}

SID_EXPORT tchar* sid_str_convert_tstr_secure(tchar* dst, const schar* src,
                                              uindex length) {
#ifdef SID_WIDE_TCHAR
  return sid_str_convert_wstr_secure(dst, src, length);
#else
  return sid_str_copy_secure(dst, src, length);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_wstr_convert_str_secure(schar* dst, const wchar* src,
                                              uindex length) {
  return sid_wstr_convert_str_offset_secure(dst, src, length, 0, 0);
}

SID_EXPORT tchar* sid_wstr_convert_tstr_secure(tchar* dst, const wchar* src,
                                               uindex length) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy_secure(dst, src, length);
#else
  return sid_wstr_convert_str_secure(dst, src, length);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_tstr_convert_str_secure(schar* dst, const tchar* src,
                                              uindex length) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_convert_str_secure(dst, src, length);
#else
  return sid_str_copy_secure(dst, src, length);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT wchar* sid_tstr_convert_wstr_secure(wchar* dst, const tchar* src,
                                               uindex length) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy_secure(dst, src, length);
#else
  return sid_str_convert_wstr_secure(dst, src, length);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT wchar* sid_str_convert_wstr_offset(wchar* dst, const schar* src,
                                              uindex dst_offset,
                                              uindex src_offset) {
  SID_ASSERT(src != SID_NULL, "Source string provided is null!");
  SID_ASSERT(dst != SID_NULL, "Destination string provided is null!");
#ifdef SID_DEBUG
  uindex count =
#endif  // SID_DEBUG
      mbstowcs(dst + dst_offset, src + src_offset, sid_str_len_with_null(src));
#ifdef SID_DEBUG
  SID_ASSERT(count > 0, "An error occurred while copying a string");
#endif  // SID_DEBUG
  return dst;
}

SID_EXPORT tchar* sid_str_convert_tstr_offset(tchar* dst, const schar* src,
                                              uindex dst_offset,
                                              uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_str_convert_wstr_offset(dst, src, dst_offset, src_offset);
#else
  return sid_str_copy_offset(dst, src, dst_offset, src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_wstr_convert_str_offset(schar* dst, const wchar* src,
                                              uindex dst_offset,
                                              uindex src_offset) {
#ifdef SID_DEBUG
  uindex count =
#endif  // SID_DEBUG
      wcstombs(dst + dst_offset, src + src_offset, sid_wstr_len_with_null(src));
#ifdef SID_DEBUG
  SID_ASSERT(count > 0, "An error occurred while copying a string");
#endif  // SID_DEBUG
  return dst;
}

SID_EXPORT tchar* sid_wstr_convert_tstr_offset(tchar* dst, const wchar* src,
                                               uindex dst_offset,
                                               uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy_offset(dst, src, dst_offset, src_offset);
#else
  return sid_wstr_convert_str_offset(dst, src, dst_offset, src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_tstr_convert_str_offset(schar* dst, const tchar* src,
                                              uindex dst_offset,
                                              uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_convert_str_offset(dst, src, dst_offset, src_offset);
#else
  return sid_str_copy_offset(dst, src, dst_offset, src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT wchar* sid_tstr_convert_wstr_offset(wchar* dst, const tchar* src,
                                               uindex dst_offset,
                                               uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy_offset(dst, src, dst_offset, src_offset);
#else
  return sid_str_convert_wstr_offset(dst, src, dst_offset, src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT wchar* sid_str_convert_wstr_offset_secure(wchar* dst,
                                                     const schar* src,
                                                     uindex length,
                                                     uindex dst_offset,
                                                     uindex src_offset) {
  SID_ASSERT(src != SID_NULL, "Source string provided is null!");
  SID_ASSERT(dst != SID_NULL, "Destination string provided is null!");
#ifdef SID_MSVC
  uindex out_count;
#ifdef SID_DEBUG
  error_code result =
#endif  // SID_DEBUG
      mbstowcs_s(&out_count, dst + dst_offset, length + 1, src + src_offset,
                 length);
#ifdef SID_DEBUG
  SID_ASSERT(result == 0, "An error occurred while copying a string");
#endif  // SID_DEBUG
#else
  mbstowcs(dst + dst_offset, src + src_offset, length);
#endif  // SID_MSVC
  return dst;
}

SID_EXPORT tchar* sid_str_convert_tstr_offset_secure(tchar* dst,
                                                     const schar* src,
                                                     uindex length,
                                                     uindex dst_offset,
                                                     uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_str_convert_wstr_offset_secure(dst, src, length, dst_offset,
                                            src_offset);
#else
  return sid_str_copy_offset_secure(dst, src, length, dst_offset, src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_wstr_convert_str_offset_secure(schar* dst,
                                                     const wchar* src,
                                                     uindex length,
                                                     uindex dst_offset,
                                                     uindex src_offset) {
  SID_ASSERT(src != SID_NULL, "Source string provided is null!");
  SID_ASSERT(dst != SID_NULL, "Destination string provided is null!");
#ifdef SID_MSVC
  uindex out_count;
#ifdef SID_DEBUG
  error_code result =
#endif  // SID_DEBUG
      wcstombs_s(&out_count, dst + dst_offset, length + 1, src + src_offset,
                 length);
#ifdef SID_DEBUG
  SID_ASSERT(result == 0, "An error occurred while copying a string");
#endif  // SID_DEBUG
#else
  wcstombs(dst + dst_offset, src + src_offset, length);
#endif  // SID_MSVC
  return dst;
}

SID_EXPORT tchar* sid_wstr_convert_tstr_offset_secure(tchar* dst,
                                                      const wchar* src,
                                                      uindex length,
                                                      uindex dst_offset,
                                                      uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy_offset_secure(dst, src, length, dst_offset, src_offset);
#else
  return sid_wstr_convert_str_offset_secure(dst, src, length, dst_offset,
                                            src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar* sid_tstr_convert_str_offset_secure(schar* dst,
                                                     const tchar* src,
                                                     uindex length,
                                                     uindex dst_offset,
                                                     uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_convert_str_offset_secure(dst, src, length, dst_offset,
                                            src_offset);
#else
  return sid_str_copy_offset_secure(dst, src, length, dst_offset, src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT wchar* sid_tstr_convert_wstr_offset_secure(wchar* dst,
                                                      const tchar* src,
                                                      uindex length,
                                                      uindex dst_offset,
                                                      uindex src_offset) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_copy_offset_secure(dst, src, length, dst_offset, src_offset);
#else
  return sid_str_convert_wstr_offset_secure(dst, src, length, dst_offset,
                                            src_offset);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT uindex sid_str_len(const schar* str) { return strlen(str); }

SID_EXPORT uindex sid_wstr_len(const wchar* str) { return wcslen(str); }

SID_EXPORT uindex sid_tstr_len(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_len(str);
#else
  return sid_str_len(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT uindex sid_str_len_with_null(const schar* str) {
  return sid_str_len(str) + 1;
}

SID_EXPORT uindex sid_wstr_len_with_null(const wchar* str) {
  return sid_wstr_len(str) + 1;
}

SID_EXPORT uindex sid_tstr_len_with_null(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_len_with_null(str);
#else
  return sid_str_len_with_null(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_fill_with(schar* str, schar c) {
  sid_str_fill_with_offset(str, c, 0, 0);
}

SID_EXPORT void sid_wstr_fill_with(wchar* str, wchar c) {
  sid_wstr_fill_with_offset(str, c, 0, 0);
}

SID_EXPORT void sid_tstr_fill_with(tchar* str, tchar c) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_fill_with(str, c);
#else
  sid_str_fill_with(str, c);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_fill_with_secure(schar* str, uindex str_length,
                                         schar c) {
  sid_str_fill_with_offset_secure(str, str_length, c, 0, SID_INVALID_INDEX);
}

SID_EXPORT void sid_wstr_fill_with_secure(wchar* str, uindex str_length,
                                          wchar c) {
  sid_wstr_fill_with_offset_secure(str, str_length, c, 0, SID_INVALID_INDEX);
}

SID_EXPORT void sid_tstr_fill_with_secure(tchar* str, uindex str_length,
                                          tchar c) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_fill_with_secure(str, str_length, c);
#else
  sid_str_fill_with_secure(str, str_length, c);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_fill_with_offset(schar* str, schar c, uindex offset,
                                         uindex length) {
  SID_ASSERT(str != SID_NULL, "String provided is null!");
  uindex str_length = sid_str_len(str);

  if (str_length == 0) {
    return;
  }

  SID_ASSERT(offset < str_length, "Offset provided is too big!");
  SID_ASSERT(length == SID_INVALID_INDEX || offset + length < str_length,
             "Length provided is too big!");

  if (length == SID_INVALID_INDEX) {
    length = str_length - offset;
  }

  uindex max = offset + length;

  for (uindex i = offset; i < max; ++i) {
    str[i] = c;
  }
}

SID_EXPORT void sid_wstr_fill_with_offset(wchar* str, wchar c, uindex offset,
                                          uindex length) {
  SID_ASSERT(str != SID_NULL, "String provided is null!");
  uindex str_length = sid_wstr_len(str);

  if (str_length == 0) {
    return;
  }

  SID_ASSERT(offset < str_length, "Offset provided is too big!");
  SID_ASSERT(length == SID_INVALID_INDEX || offset + length < str_length,
             "Length provided is too big!");

  if (length == SID_INVALID_INDEX) {
    length = str_length - offset;
  }

  uindex max = offset + length;

  for (uindex i = offset; i < max; ++i) {
    str[i] = c;
  }
}

SID_EXPORT void sid_tstr_fill_with_offset(tchar* str, tchar c, uindex offset,
                                          uindex length) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_fill_with_offset(str, c, offset, length);
#else
  sid_str_fill_with_offset(str, c, offset, length);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_fill_with_offset_secure(schar* str, uindex str_length,
                                                schar c, uindex offset,
                                                uindex length) {
  SID_ASSERT(str != SID_NULL, "String provided is null!");

  if (str_length == 0) {
    return;
  }

  SID_ASSERT(offset < str_length, "Offset provided is too big!");
  SID_ASSERT(length == SID_INVALID_INDEX || offset + length < str_length,
             "Length provided is too big!");

  if (length == SID_INVALID_INDEX) {
    length = str_length - offset;
  }

  uindex max = offset + length;

  for (uindex i = offset; i < max; ++i) {
    str[i] = c;
  }
}

SID_EXPORT void sid_wstr_fill_with_offset_secure(wchar* str, uindex str_length,
                                                 wchar c, uindex offset,
                                                 uindex length) {
  SID_ASSERT(str != SID_NULL, "String provided is null!");

  if (str_length == 0) {
    return;
  }

  SID_ASSERT(offset < str_length, "Offset provided is too big!");
  SID_ASSERT(length == SID_INVALID_INDEX || offset + length < str_length,
             "Length provided is too big!");

  if (length == SID_INVALID_INDEX) {
    length = str_length - offset;
  }

  uindex max = offset + length;

  for (uindex i = offset; i < max; ++i) {
    str[i] = c;
  }
}

SID_EXPORT void sid_tstr_fill_with_offset_secure(tchar* str, uindex str_length,
                                                 tchar c, uindex offset,
                                                 uindex length) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_fill_with_offset_secure(str, str_length, c, offset, length);
#else
  sid_str_fill_with_offset_secure(str, str_length, c, offset, length);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar sid_schar_to_upper(schar c) { return (schar)toupper(c); }

SID_EXPORT wchar sid_wchar_to_upper(wchar c) { return (wchar)towupper(c); }

SID_EXPORT tchar sid_tchar_to_upper(tchar c) {
#ifdef SID_WIDE_TCHAR
  return sid_wchar_to_upper(c);
#else
  return sid_schar_to_upper(c);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT schar sid_schar_to_lower(schar c) { return (schar)tolower(c); }

SID_EXPORT wchar sid_wchar_to_lower(wchar c) { return (wchar)towlower(c); }

SID_EXPORT tchar sid_tchar_to_lower(tchar c) {
#ifdef SID_WIDE_TCHAR
  return sid_wchar_to_lower(c);
#else
  return sid_schar_to_lower(c);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT u8 sid_str_parse_u8(const schar* str) {
  return (u8)sid_str_parse_u32(str);
}

SID_EXPORT u8 sid_wstr_parse_u8(const wchar* str) {
  return (u8)sid_wstr_parse_u32(str);
}

SID_EXPORT u8 sid_tstr_parse_u8(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_u8(str);
#else
  return sid_str_parse_u8(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT u16 sid_str_parse_u16(const schar* str) {
  return (u16)sid_str_parse_u32(str);
}

SID_EXPORT u16 sid_wstr_parse_u16(const wchar* str) {
  return (u16)sid_wstr_parse_u32(str);
}

SID_EXPORT u16 sid_tstr_parse_u16(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_u16(str);
#else
  return sid_str_parse_u16(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT u32 sid_str_parse_u32(const schar* str) {
  schar* str_end;
  u32 value = (u32)strtoul(str, &str_end, 10);
  SID_ASSERT(str_end != str, "Invalid argument!");
  SID_ASSERT(errno != ERANGE, "Out of range!");
  return value;
}

SID_EXPORT u32 sid_wstr_parse_u32(const wchar* str) {
  wchar* str_end;
  u32 value = (u32)wcstoul(str, &str_end, 10);
  SID_ASSERT(str_end != str, "Invalid argument!");
  SID_ASSERT(errno != ERANGE, "Out of range!");
  return value;
}

SID_EXPORT u32 sid_tstr_parse_u32(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_u32(str);
#else
  return sid_str_parse_u32(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT u64 sid_str_parse_u64(const schar* str) {
  schar* str_end;
  u64 value = (u64)strtoull(str, &str_end, 10);
  SID_ASSERT(str_end != str, "Invalid argument!");
  SID_ASSERT(errno != ERANGE, "Out of range!");
  return value;
}

SID_EXPORT u64 sid_wstr_parse_u64(const wchar* str) {
  wchar* str_end;
  u64 value = (u64)wcstoull(str, &str_end, 10);
  SID_ASSERT(str_end != str, "Invalid argument!");
  SID_ASSERT(errno != ERANGE, "Out of range!");
  return value;
}

SID_EXPORT u64 sid_tstr_parse_u64(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_u64(str);
#else
  return sid_str_parse_u64(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT s8 sid_str_parse_s8(const schar* str) { return (u8)atoi(str); }

SID_EXPORT s8 sid_wstr_parse_s8(const wchar* str) {
#ifdef SID_MSVC
  return (s8)_wtoi(str);
#else
  wchar* p;
  return (s8)wcstol(str, &p, 10);
#endif  // SID_MSVC
}

SID_EXPORT s8 sid_tstr_parse_s8(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_s8(str);
#else
  return sid_str_parse_s8(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT s16 sid_str_parse_s16(const schar* str) { return (s16)atoi(str); }

SID_EXPORT s16 sid_wstr_parse_s16(const wchar* str) {
#ifdef SID_MSVC
  return (s16)_wtoi(str);
#else
  wchar* p;
  return (s16)wcstol(str, &p, 10);
#endif  // SID_MSVC
}

SID_EXPORT s16 sid_tstr_parse_s16(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_s16(str);
#else
  return sid_str_parse_s16(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT s32 sid_str_parse_s32(const schar* str) { return (s32)atoi(str); }

SID_EXPORT s32 sid_wstr_parse_s32(const wchar* str) {
#ifdef SID_MSVC
  return (s32)_wtoi(str);
#else
  wchar* p;
  return (s32)wcstol(str, &p, 10);
#endif  // SID_MSVC
}

SID_EXPORT s32 sid_tstr_parse_s32(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_s32(str);
#else
  return sid_str_parse_s32(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT s64 sid_str_parse_s64(const schar* str) { return atoll(str); }

SID_EXPORT s64 sid_wstr_parse_s64(const wchar* str) {
  wchar* p;
  return (s64)wcstoll(str, &p, 10);
}

SID_EXPORT s64 sid_tstr_parse_s64(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_s64(str);
#else
  return sid_str_parse_s64(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT f32 sid_str_parse_f32(const schar* str) { return (f32)atof(str); }

SID_EXPORT f32 sid_wstr_parse_f32(const wchar* str) {
  wchar* p;
  return (f32)wcstod(str, &p);
}

SID_EXPORT f32 sid_tstr_parse_f32(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_f32(str);
#else
  return sid_str_parse_f32(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT f64 sid_str_parse_f64(const schar* str) { return atof(str); }

SID_EXPORT f64 sid_wstr_parse_f64(const wchar* str) {
  wchar* p;
  return wcstod(str, &p);
}

SID_EXPORT f64 sid_tstr_parse_f64(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_f64(str);
#else
  return sid_str_parse_f64(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT uindex sid_str_parse_uindex(const schar* str) {
  schar* str_end;
  uindex value = (uindex)strtoull(str, &str_end, 10);
  SID_ASSERT(str_end != str, "Invalid argument!");
  SID_ASSERT(errno != ERANGE, "Out of range!");
  return value;
}

SID_EXPORT uindex sid_wstr_parse_uindex(const wchar* str) {
  wchar* str_end;
  uindex value = (uindex)wcstoull(str, &str_end, 10);
  SID_ASSERT(str_end != str, "Invalid argument!");
  SID_ASSERT(errno != ERANGE, "Out of range!");
  return value;
}

SID_EXPORT uindex sid_tstr_parse_uindex(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_uindex(str);
#else
  return sid_str_parse_uindex(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT ux sid_str_parse_ux(const schar* str) {
#ifdef SID_64
  return sid_str_parse_u64(str);
#else
  return sid_str_parse_u32(str);
#endif  // SID_64
}

SID_EXPORT ux sid_wstr_parse_ux(const wchar* str) {
#ifdef SID_64
  return sid_wstr_parse_u64(str);
#else
  return sid_wstr_parse_u32(str);
#endif  // SID_64
}

SID_EXPORT ux sid_tstr_parse_ux(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_ux(str);
#else
  return sid_str_parse_ux(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT sx sid_str_parse_sx(const schar* str) {
#ifdef SID_64
  return sid_str_parse_s64(str);
#else
  return sid_str_parse_s32(str);
#endif  // SID_64
}

SID_EXPORT sx sid_wstr_parse_sx(const wchar* str) {
#ifdef SID_64
  return sid_wstr_parse_s64(str);
#else
  return sid_wstr_parse_s32(str);
#endif  // SID_64
}

SID_EXPORT sx sid_tstr_parse_sx(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_sx(str);
#else
  return sid_str_parse_sx(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT fx sid_str_parse_fx(const schar* str) {
#ifdef SID_64
  return sid_str_parse_f64(str);
#else
  return sid_str_parse_f32(str);
#endif  // SID_64
}

SID_EXPORT fx sid_wstr_parse_fx(const wchar* str) {
#ifdef SID_64
  return sid_wstr_parse_f64(str);
#else
  return sid_wstr_parse_f32(str);
#endif  // SID_64
}

SID_EXPORT fx sid_tstr_parse_fx(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_fx(str);
#else
  return sid_str_parse_fx(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT b8 sid_str_parse_b8(const schar* str) {
  if (str == SID_NULL) {
    return SID_FALSE;
  }

  uindex length = sid_str_len(str);

  if (length == 0) {
    return SID_FALSE;
  }

  if (length == 1) {
    return str[0] != '0';
  }

  if (length != 5) {
    return true;
  }

  const schar* false_str = "false";

  for (u8 i = 0; i < 5; ++i) {
    if (sid_schar_to_lower(str[i]) != false_str[i]) {
      return true;
    }
  }

  return false;
}

SID_EXPORT b8 sid_wstr_parse_b8(const wchar* str) {
  if (str == SID_NULL) {
    return SID_FALSE;
  }

  uindex length = sid_wstr_len(str);

  if (length == 0) {
    return SID_FALSE;
  }

  if (length == 1) {
    return str[0] != L'0';
  }

  if (length != 5) {
    return true;
  }

  const wchar* false_str = L"false";

  for (u8 i = 0; i < 5; ++i) {
    if (sid_wchar_to_lower(str[i]) != false_str[i]) {
      return true;
    }
  }

  return false;
}

SID_EXPORT b8 sid_tstr_parse_b8(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_b8(str);
#else
  return sid_str_parse_b8(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT s32 sid_str_parse_string_id(const schar* str) {
  return sid_str_parse_u32(str);
}

SID_EXPORT s32 sid_wstr_parse_string_id(const wchar* str) {
  return sid_wstr_parse_u32(str);
}

SID_EXPORT s32 sid_tstr_parse_string_id(const tchar* str) {
#ifdef SID_WIDE_TCHAR
  return sid_wstr_parse_string_id(str);
#else
  return sid_str_parse_string_id(str);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_u8(u8 number, schar* buffer, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%" PRIu8, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_u8(u8 number, wchar* buffer, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%" PRIu8, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_u8(u8 number, tchar* buffer, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_u8(number, buffer, out_len);
#else
  sid_str_convert_u8(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_u8_secure(u8 number, schar* buffer,
                                          uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%" PRIu8, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_u8_secure(u8 number, wchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
// TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len =
      _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%" PRIu8, number);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%" PRIu8, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_u8_secure(u8 number, tchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_u8_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_u8_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_u16(u16 number, schar* buffer,
                                    uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%" PRIu16, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_u16(u16 number, wchar* buffer,
                                     uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%" PRIu16, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_u16(u16 number, tchar* buffer,
                                     uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_u16(number, buffer, out_len);
#else
  sid_str_convert_u16(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_u16_secure(u16 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%" PRIu16, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_u16_secure(u16 number, wchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
// TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len =
      _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%" PRIu16, number);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%" PRIu16, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_u16_secure(u16 number, tchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_u16_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_u16_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_u32(u32 number, schar* buffer,
                                    uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%" PRIu32, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_u32(u32 number, wchar* buffer,
                                     uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%" PRIu32, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_u32(u32 number, tchar* buffer,
                                     uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_u32(number, buffer, out_len);
#else
  sid_str_convert_u32(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_u32_secure(u32 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%" PRIu32, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_u32_secure(u32 number, wchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
// TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len =
      _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%" PRIu32, number);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%" PRIu32, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_u32_secure(u32 number, tchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_u32_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_u32_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_u64(u64 number, schar* buffer,
                                    uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%" PRIu64, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_u64(u64 number, wchar* buffer,
                                     uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%" PRIu64, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_u64(u64 number, tchar* buffer,
                                     uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_u64(number, buffer, out_len);
#else
  sid_str_convert_u64(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_u64_secure(u64 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%" PRIu64, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_u64_secure(u64 number, wchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
// TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len =
      _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%" PRIu64, number);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%" PRIu64, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_u64_secure(u64 number, tchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_u64_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_u64_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_s8(s8 number, schar* buffer, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%" PRId8, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_s8(s8 number, wchar* buffer, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%" PRId8, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_s8(s8 number, tchar* buffer, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_s8(number, buffer, out_len);
#else
  sid_str_convert_s8(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_s8_secure(s8 number, schar* buffer,
                                          uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%" PRId8, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_s8_secure(s8 number, wchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
// TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len =
      _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%" PRId8, number);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%" PRId8, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_s8_secure(s8 number, tchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_s8_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_s8_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_s16(s16 number, schar* buffer,
                                    uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%" PRId16, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_s16(s16 number, wchar* buffer,
                                     uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%" PRId16, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_s16(s16 number, tchar* buffer,
                                     uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_s16(number, buffer, out_len);
#else
  sid_str_convert_s16(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_s16_secure(s16 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%" PRId16, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_s16_secure(s16 number, wchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
// TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len =
      _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%" PRId16, number);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%" PRId16, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_s16_secure(s16 number, tchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_s16_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_s16_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_s32(s32 number, schar* buffer,
                                    uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%" PRId32, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_s32(s32 number, wchar* buffer,
                                     uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%" PRId32, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_s32(s32 number, tchar* buffer,
                                     uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_s32(number, buffer, out_len);
#else
  sid_str_convert_s32(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_s32_secure(s32 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%" PRId32, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_s32_secure(s32 number, wchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
// TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len =
      _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%" PRId32, number);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%" PRId32, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_s32_secure(s32 number, tchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_s32_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_s32_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_s64(s64 number, schar* buffer,
                                    uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%" PRId64, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_s64(s64 number, wchar* buffer,
                                     uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%" PRId64, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_s64(s64 number, tchar* buffer,
                                     uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_s64(number, buffer, out_len);
#else
  sid_str_convert_s64(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_s64_secure(s64 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%" PRId64, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_s64_secure(s64 number, wchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
// TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len =
      _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%" PRId64, number);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%" PRId64, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_s64_secure(s64 number, tchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_s64_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_s64_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_f32(f32 number, u8 precision, schar* buffer,
                                    uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  schar format[10];
  snprintf(format, 9, "%%.%df", precision);
  s32 len = sprintf(buffer, format, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_f32(f32 number, u8 precision, wchar* buffer,
                                     uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  wchar format[10];
  swprintf(format, 9, L"%%.%df", precision);
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, format, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_f32(f32 number, u8 precision, tchar* buffer,
                                     uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_f32(number, precision, buffer, out_len);
#else
  sid_str_convert_f32(number, precision, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_f32_secure(f32 number, u8 precision,
                                           schar* buffer, uindex buffer_len,
                                           uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  schar format[10];
  snprintf(format, 9, "%%.%df", precision);
  s32 len = snprintf(buffer, buffer_len - 1, format, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_f32_secure(f32 number, u8 precision,
                                            wchar* buffer, uindex buffer_len,
                                            uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  wchar format[10];

#ifdef SID_MSVC
  _snwprintf_s(format, 10, 9, L"%%.%df", precision);
  s32 len = _snwprintf_s(buffer, buffer_len, buffer_len - 1, format, number);
#else
  swprintf(format, 9, L"%%.%df", precision);
  s32 len = swprintf(buffer, buffer_len - 1, format, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_f32_secure(f32 number, u8 precision,
                                            tchar* buffer, uindex buffer_len,
                                            uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_f32_secure(number, precision, buffer, buffer_len, out_len);
#else
  sid_str_convert_f32_secure(number, precision, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_f64(f64 number, u8 precision, schar* buffer,
                                    uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  schar format[10];
  snprintf(format, 9, "%%.%dlf", precision);
  s32 len = sprintf(buffer, format, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_f64(f64 number, u8 precision, wchar* buffer,
                                     uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  wchar format[10];
  swprintf(format, 9, L"%%.%dlf", precision);
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, format, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_f64(f64 number, u8 precision, tchar* buffer,
                                     uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_f64(number, precision, buffer, out_len);
#else
  sid_str_convert_f64(number, precision, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_f64_secure(f64 number, u8 precision,
                                           schar* buffer, uindex buffer_len,
                                           uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  schar format[10];
  snprintf(format, 9, "%%.%dlf", precision);
  s32 len = snprintf(buffer, buffer_len - 1, format, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_f64_secure(f64 number, u8 precision,
                                            wchar* buffer, uindex buffer_len,
                                            uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  wchar format[10];

#ifdef SID_MSVC
  _snwprintf_s(format, 10, 9, L"%%.%dlf", precision);
  s32 len = _snwprintf_s(buffer, buffer_len, buffer_len - 1, format, number);
#else
  swprintf(format, 9, L"%%.%dlf", precision);
  s32 len = swprintf(buffer, buffer_len - 1, format, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_f64_secure(f64 number, u8 precision,
                                            tchar* buffer, uindex buffer_len,
                                            uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_f64_secure(number, precision, buffer, buffer_len, out_len);
#else
  sid_str_convert_f64_secure(number, precision, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_uindex(uindex number, schar* buffer,
                                       uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%" PRIu64, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_uindex(uindex number, wchar* buffer,
                                        uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len =
      swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%" PRIu64, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_uindex(uindex number, tchar* buffer,
                                        uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_uindex(number, buffer, out_len);
#else
  sid_str_convert_uindex(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_uindex_secure(uindex number, schar* buffer,
                                              uindex buffer_len,
                                              uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%" PRIu64, number);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_uindex_secure(uindex number, wchar* buffer,
                                               uindex buffer_len,
                                               uindex* out_len) {
// TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len =
      _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%" PRIu64, number);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%" PRIu64, number);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_uindex_secure(uindex number, tchar* buffer,
                                               uindex buffer_len,
                                               uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_uindex_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_uindex_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_ux(ux number, schar* buffer, uindex* out_len) {
#ifdef SID_64
  sid_str_convert_u64(number, buffer, out_len);
#else
  sid_str_convert_u32(number, buffer, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_wstr_convert_ux(ux number, wchar* buffer, uindex* out_len) {
#ifdef SID_64
  sid_wstr_convert_u64(number, buffer, out_len);
#else
  sid_wstr_convert_u32(number, buffer, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_tstr_convert_ux(ux number, tchar* buffer, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_ux(number, buffer, out_len);
#else
  sid_str_convert_ux(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_ux_secure(ux number, schar* buffer,
                                          uindex buffer_len, uindex* out_len) {
#ifdef SID_64
  sid_str_convert_u64_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_u32_secure(number, buffer, buffer_len, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_wstr_convert_ux_secure(ux number, wchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
#ifdef SID_64
  sid_wstr_convert_u64_secure(number, buffer, buffer_len, out_len);
#else
  sid_wstr_convert_u32_secure(number, buffer, buffer_len, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_tstr_convert_ux_secure(ux number, tchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_ux_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_ux_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_sx(sx number, schar* buffer, uindex* out_len) {
#ifdef SID_64
  sid_str_convert_u64(number, buffer, out_len);
#else
  sid_str_convert_u32(number, buffer, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_wstr_convert_sx(sx number, wchar* buffer, uindex* out_len) {
#ifdef SID_64
  sid_wstr_convert_u64(number, buffer, out_len);
#else
  sid_wstr_convert_u32(number, buffer, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_tstr_convert_sx(sx number, tchar* buffer, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_sx(number, buffer, out_len);
#else
  sid_str_convert_sx(number, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_sx_secure(sx number, schar* buffer,
                                          uindex buffer_len, uindex* out_len) {
#ifdef SID_64
  sid_str_convert_s64_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_s32_secure(number, buffer, buffer_len, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_wstr_convert_sx_secure(sx number, wchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
#ifdef SID_64
  sid_wstr_convert_s64_secure(number, buffer, buffer_len, out_len);
#else
  sid_wstr_convert_s32_secure(number, buffer, buffer_len, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_tstr_convert_sx_secure(sx number, tchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_sx_secure(number, buffer, buffer_len, out_len);
#else
  sid_str_convert_sx_secure(number, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_fx(fx number, u8 precision, schar* buffer,
                                   uindex* out_len) {
#ifdef SID_64
  sid_str_convert_f64(number, precision, buffer, out_len);
#else
  sid_str_convert_f32(number, precision, buffer, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_wstr_convert_fx(fx number, u8 precision, wchar* buffer,
                                    uindex* out_len) {
#ifdef SID_64
  sid_wstr_convert_f64(number, precision, buffer, out_len);
#else
  sid_wstr_convert_f32(number, precision, buffer, out_len);
#endif  // SID_64
}

SID_EXPORT void sid_tstr_convert_fx(fx number, u8 precision, tchar* buffer,
                                    uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_fx(number, precision, buffer, out_len);
#else
  sid_str_convert_fx(number, precision, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_fx_secure(fx number, u8 precision,
                                          schar* buffer, uindex buffer_len,
                                          uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_str_convert_f64_secure(number, precision, buffer, buffer_len, out_len);
#else
  sid_str_convert_f64_secure(number, precision, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_wstr_convert_fx_secure(fx number, u8 precision,
                                           wchar* buffer, uindex buffer_len,
                                           uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_f64_secure(number, precision, buffer, buffer_len, out_len);
#else
  sid_wstr_convert_f64_secure(number, precision, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_tstr_convert_fx_secure(fx number, u8 precision,
                                           tchar* buffer, uindex buffer_len,
                                           uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_fx_secure(number, precision, buffer, buffer_len, out_len);
#else
  sid_str_convert_fx_secure(number, precision, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_b8(b8 boolean, schar* buffer, uindex* out_len) {
  s32 len = sprintf(buffer, "%s", boolean == SID_TRUE ? "true" : "false");

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_b8(b8 boolean, wchar* buffer,
                                    uindex* out_len) {
  s32 len = swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%ls",
                     boolean == SID_TRUE ? L"true" : L"false");

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_b8(b8 boolean, tchar* buffer,
                                    uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_b8(boolean, buffer, out_len);
#else
  sid_str_convert_b8(boolean, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_b8_secure(b8 boolean, schar* buffer,
                                          uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%s",
                     boolean == SID_TRUE ? "true" : "false");

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_b8_secure(b8 boolean, wchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len = _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%ls",
                         boolean == SID_TRUE ? L"true" : L"false");
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%ls",
                     boolean == SID_TRUE ? L"true" : L"false");
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_b8_secure(b8 boolean, tchar* buffer,
                                           uindex buffer_len, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_b8_secure(boolean, buffer, buffer_len, out_len);
#else
  sid_str_convert_b8_secure(boolean, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_string_id(sid_string_id string_id,
                                          schar* buffer, uindex* out_len) {
  sid_str_convert_u32(string_id, buffer, out_len);
}

SID_EXPORT void sid_wstr_convert_string_id(sid_string_id string_id,
                                           wchar* buffer, uindex* out_len) {
  sid_wstr_convert_u32(string_id, buffer, out_len);
}

SID_EXPORT void sid_tstr_convert_string_id(sid_string_id string_id,
                                           tchar* buffer, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_string_id(string_id, buffer, out_len);
#else
  sid_str_convert_string_id(string_id, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_string_id_secure(sid_string_id string_id,
                                                 schar* buffer,
                                                 uindex buffer_len,
                                                 uindex* out_len) {
  sid_str_convert_u32_secure(string_id, buffer, buffer_len, out_len);
}

SID_EXPORT void sid_wstr_convert_string_id_secure(sid_string_id string_id,
                                                  wchar* buffer,
                                                  uindex buffer_len,
                                                  uindex* out_len) {
  sid_wstr_convert_u32_secure(string_id, buffer, buffer_len, out_len);
}

SID_EXPORT void sid_tstr_convert_string_id_secure(sid_string_id string_id,
                                                  tchar* buffer,
                                                  uindex buffer_len,
                                                  uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_string_id_secure(string_id, buffer, buffer_len, out_len);
#else
  sid_str_convert_string_id_secure(string_id, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_str_convert_hex(u8 byte, schar* buffer, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = sprintf(buffer, "%02x", byte);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_str_convert_hex_secure(u8 byte, schar* buffer,
                                           uindex buffer_len, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = snprintf(buffer, buffer_len, "%02x", byte);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_hex(u8 byte, wchar* buffer, uindex* out_len) {
  // TODO(m4jr0): Optimize function.
  s32 len = swprintf(buffer, SID_WSTR_MAX_UNSECURE_BUFFER_COUNT, L"%02x", byte);

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_wstr_convert_hex_secure(u8 byte, wchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
  // TODO(m4jr0): Optimize function.
#ifdef SID_MSVC
  s32 len = _snwprintf_s(buffer, buffer_len, buffer_len - 1, L"%02x", byte);
#else
  s32 len = swprintf(buffer, buffer_len - 1, L"%02x", byte);
#endif  // SID_MSVC

  if (out_len != SID_NULL) {
    *out_len = len >= 0 ? (uindex)len : SID_INVALID_INDEX;
  }
}

SID_EXPORT void sid_tstr_convert_hex(u8 byte, tchar* buffer, uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_hex(byte, buffer, out_len);
#else
  sid_str_convert_hex(byte, buffer, out_len);
#endif  // SID_WIDE_TCHAR
}

SID_EXPORT void sid_tstr_convert_hex_secure(u8 byte, tchar* buffer,
                                            uindex buffer_len,
                                            uindex* out_len) {
#ifdef SID_WIDE_TCHAR
  sid_wstr_convert_hex_secure(byte, buffer, buffer_len, out_len);
#else
  sid_str_convert_hex_secure(byte, buffer, buffer_len, out_len);
#endif  // SID_WIDE_TCHAR
}
