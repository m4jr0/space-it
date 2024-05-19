// Copyright 2024 m4jr0. All Rights Reserved.
// Use of this source code is governed by the MIT
// license that can be found in the LICENSE file.

#ifndef SID_LIB_STRING_H_
#define SID_LIB_STRING_H_

#include "sid_precompile.h"

#include "sid/string_id.h"

SID_EXPORT s32 sid_str_compare(const schar* str1, const schar* str2);
SID_EXPORT s32 sid_wstr_compare(const wchar* str1, const wchar* str2);
SID_EXPORT s32 sid_tstr_compare(const tchar* str1, const tchar* str2);
SID_EXPORT s32 sid_str_compare_secure(const schar* str1, const schar* str2,
                                      uindex length);
SID_EXPORT s32 sid_wstr_compare_secure(const wchar* str1, const wchar* str2,
                                       uindex length);
SID_EXPORT s32 sid_tstr_compare_secure(const tchar* str1, const tchar* str2,
                                       uindex length);
SID_EXPORT b8 sid_str_equal(const schar* str1, const schar* str2);
SID_EXPORT b8 sid_wstr_equal(const wchar* str1, const wchar* str2);
SID_EXPORT b8 sid_tstr_equal(const tchar* str1, const tchar* str2);
SID_EXPORT b8 sid_str_equal_secure(const schar* str1, uindex str1_len,
                                   const schar* str2, uindex str2_len);
SID_EXPORT b8 sid_wstr_equal_secure(const wchar* str1, uindex str1_len,
                                    const wchar* str2, uindex str2_len);
SID_EXPORT b8 sid_tstr_equal_secure(const tchar* str1, uindex str1_len,
                                    const tchar* str2, uindex str2_len);
SID_EXPORT s32 sid_str_compare_insensitive(const schar* str1,
                                           const schar* str2);
SID_EXPORT s32 sid_wstr_compare_insensitive(const wchar* str1,
                                            const wchar* str2);
SID_EXPORT s32 sid_tstr_compare_insensitive(const tchar* str1,
                                            const tchar* str2);
SID_EXPORT s32 sid_str_compare_insensitive_secure(const schar* str1,
                                                  const schar* str2,
                                                  uindex length);
SID_EXPORT s32 sid_wstr_compare_insensitive_secure(const wchar* str1,
                                                   const wchar* str2,
                                                   uindex length);
SID_EXPORT s32 sid_tstr_compare_insensitive_secure(const tchar* str1,
                                                   const tchar* str2,
                                                   uindex length);
SID_EXPORT b8 sid_str_equal_insensitive(const schar* str1, const schar* str2);
SID_EXPORT b8 sid_wstr_equal_insensitive(const wchar* str1, const wchar* str2);
SID_EXPORT b8 sid_tstr_equal_insensitive(const tchar* str1, const tchar* str2);
SID_EXPORT b8 sid_str_equal_insensitive_secure(const schar* str1,
                                               uindex str1_len,
                                               const schar* str2,
                                               uindex str2_len);
SID_EXPORT b8 sid_wstr_equal_insensitive_secure(const wchar* str1,
                                                uindex str1_len,
                                                const wchar* str2,
                                                uindex str2_len);
SID_EXPORT b8 sid_tstr_equal_insensitive_secure(const tchar* str1,
                                                uindex str1_len,
                                                const tchar* str2,
                                                uindex str2_len);
SID_EXPORT b8 sid_schar_space(schar c);
SID_EXPORT b8 sid_wchar_space(wchar c);
SID_EXPORT b8 sid_tchar_space(tchar c);
SID_EXPORT b8 sid_schar_alpha(schar c);
SID_EXPORT b8 sid_wchar_alpha(wchar c);
SID_EXPORT b8 sid_tchar_alpha(tchar c);
SID_EXPORT schar* sid_str_copy(schar* dst, const schar* src);
SID_EXPORT wchar* sid_wstr_copy(wchar* dst, const wchar* src);
SID_EXPORT tchar* sid_tstr_copy(tchar* dst, const tchar* src);
SID_EXPORT schar* sid_str_copy_secure(schar* dst, const schar* src,
                                      uindex length);
SID_EXPORT wchar* sid_wstr_copy_secure(wchar* dst, const wchar* src,
                                       uindex length);
SID_EXPORT tchar* sid_tstr_copy_secure(tchar* dst, const tchar* src,
                                       uindex length);
SID_EXPORT schar* sid_str_copy_offset(schar* dst, const schar* src,
                                      uindex dst_offset, uindex src_offset);
SID_EXPORT wchar* sid_wstr_copy_offset(wchar* dst, const wchar* src,
                                       uindex dst_offset, uindex src_offset);
SID_EXPORT tchar* sid_tstr_copy_offset(tchar* dst, const tchar* src,
                                       uindex dst_offset, uindex src_offset);
SID_EXPORT schar* sid_str_copy_offset_secure(schar* dst, const schar* src,
                                             uindex length, uindex dst_offset,
                                             uindex src_offset);
SID_EXPORT wchar* sid_wstr_copy_offset_secure(wchar* dst, const wchar* src,
                                              uindex length, uindex dst_offset,
                                              uindex src_offset);
SID_EXPORT tchar* sid_tstr_copy_offset_secure(tchar* dst, const tchar* src,
                                              uindex length, uindex dst_offset,
                                              uindex src_offset);
SID_EXPORT wchar* sid_str_convert_wstr(wchar* dst, const schar* src);
SID_EXPORT tchar* sid_str_convert_tstr(tchar* dst, const schar* src);

SID_EXPORT schar* sid_wstr_convert_str(schar* dst, const wchar* src);
SID_EXPORT tchar* sid_wstr_convert_tstr(tchar* dst, const wchar* src);

SID_EXPORT schar* sid_tstr_convert_str(schar* dst, const tchar* src);
SID_EXPORT wchar* sid_tstr_convert_wstr(wchar* dst, const tchar* src);
SID_EXPORT wchar* sid_str_convert_wstr_secure(wchar* dst, const schar* src,
                                              uindex length);
SID_EXPORT tchar* sid_str_convert_tstr_secure(tchar* dst, const schar* src,
                                              uindex length);
SID_EXPORT schar* sid_wstr_convert_str_secure(schar* dst, const wchar* src,
                                              uindex length);
SID_EXPORT tchar* sid_wstr_convert_tstr_secure(tchar* dst, const wchar* src,
                                               uindex length);
SID_EXPORT schar* sid_tstr_convert_str_secure(schar* dst, const tchar* src,
                                              uindex length);
SID_EXPORT wchar* sid_tstr_convert_wstr_secure(wchar* dst, const tchar* src,
                                               uindex length);
SID_EXPORT wchar* sid_str_convert_wstr_offset(wchar* dst, const schar* src,
                                              uindex dst_offset,
                                              uindex src_offset);
SID_EXPORT tchar* sid_str_convert_tstr_offset(tchar* dst, const schar* src,
                                              uindex dst_offset,
                                              uindex src_offset);
SID_EXPORT schar* sid_wstr_convert_str_offset(schar* dst, const wchar* src,
                                              uindex dst_offset,
                                              uindex src_offset);
SID_EXPORT tchar* sid_wstr_convert_tstr_offset(tchar* dst, const wchar* src,
                                               uindex dst_offset,
                                               uindex src_offset);
SID_EXPORT schar* sid_tstr_convert_str_offset(schar* dst, const tchar* src,
                                              uindex dst_offset,
                                              uindex src_offset);
SID_EXPORT wchar* sid_tstr_convert_wstr_offset(wchar* dst, const tchar* src,
                                               uindex dst_offset,
                                               uindex src_offset);
SID_EXPORT wchar* sid_str_convert_wstr_offset_secure(wchar* dst,
                                                     const schar* src,
                                                     uindex length,
                                                     uindex dst_offset,
                                                     uindex src_offset);
SID_EXPORT tchar* sid_str_convert_tstr_offset_secure(tchar* dst,
                                                     const schar* src,
                                                     uindex length,
                                                     uindex dst_offset,
                                                     uindex src_offset);
SID_EXPORT schar* sid_wstr_convert_str_offset_secure(schar* dst,
                                                     const wchar* src,
                                                     uindex length,
                                                     uindex dst_offset,
                                                     uindex src_offset);
SID_EXPORT tchar* sid_wstr_convert_tstr_offset_secure(tchar* dst,
                                                      const wchar* src,
                                                      uindex length,
                                                      uindex dst_offset,
                                                      uindex src_offset);
SID_EXPORT schar* sid_tstr_convert_str_offset_secure(schar* dst,
                                                     const tchar* src,
                                                     uindex length,
                                                     uindex dst_offset,
                                                     uindex src_offset);
SID_EXPORT wchar* sid_tstr_convert_wstr_offset_secure(wchar* dst,
                                                      const tchar* src,
                                                      uindex length,
                                                      uindex dst_offset,
                                                      uindex src_offset);
SID_EXPORT uindex sid_str_len(const schar* str);
SID_EXPORT uindex sid_wstr_len(const wchar* str);
SID_EXPORT uindex sid_tstr_len(const tchar* str);
SID_EXPORT uindex sid_str_len_with_null(const schar* str);
SID_EXPORT uindex sid_wstr_len_with_null(const wchar* str);
SID_EXPORT uindex sid_tstr_len_with_null(const tchar* str);
SID_EXPORT void sid_str_fill_with(schar* str, schar c);
SID_EXPORT void sid_wstr_fill_with(wchar* str, wchar c);
SID_EXPORT void sid_tstr_fill_with(tchar* str, tchar c);
SID_EXPORT void sid_str_fill_with_secure(schar* str, uindex str_length,
                                         schar c);
SID_EXPORT void sid_wstr_fill_with_secure(wchar* str, uindex str_length,
                                          wchar c);
SID_EXPORT void sid_tstr_fill_with_secure(tchar* str, uindex str_length,
                                          tchar c);
SID_EXPORT void sid_str_fill_with_offset(schar* str, schar c, uindex offset,
                                         uindex length);
SID_EXPORT void sid_wstr_fill_with_offset(wchar* str, wchar c, uindex offset,
                                          uindex length);
SID_EXPORT void sid_tstr_fill_with_offset(tchar* str, tchar c, uindex offset,
                                          uindex length);
SID_EXPORT void sid_str_fill_with_offset_secure(schar* str, uindex str_length,
                                                schar c, uindex offset,
                                                uindex length);
SID_EXPORT void sid_wstr_fill_with_offset_secure(wchar* str, uindex str_length,
                                                 wchar c, uindex offset,
                                                 uindex length);
SID_EXPORT void sid_tstr_fill_with_offset_secure(tchar* str, uindex str_length,
                                                 tchar c, uindex offset,
                                                 uindex length);
SID_EXPORT schar sid_schar_to_upper(schar c);
SID_EXPORT wchar sid_wchar_to_upper(wchar c);
SID_EXPORT tchar sid_tchar_to_upper(tchar c);
SID_EXPORT schar sid_schar_to_lower(schar c);
SID_EXPORT wchar sid_wchar_to_lower(wchar c);
SID_EXPORT tchar sid_tchar_to_lower(tchar c);
SID_EXPORT u8 sid_str_parse_u8(const schar* str);
SID_EXPORT u8 sid_wstr_parse_u8(const wchar* str);
SID_EXPORT u8 sid_tstr_parse_u8(const tchar* str);
SID_EXPORT u16 sid_str_parse_u16(const schar* str);
SID_EXPORT u16 sid_wstr_parse_u16(const wchar* str);
SID_EXPORT u16 sid_tstr_parse_u16(const tchar* str);
SID_EXPORT u32 sid_str_parse_u32(const schar* str);
SID_EXPORT u32 sid_wstr_parse_u32(const wchar* str);
SID_EXPORT u32 sid_tstr_parse_u32(const tchar* str);
SID_EXPORT u64 sid_str_parse_u64(const schar* str);
SID_EXPORT u64 sid_wstr_parse_u64(const wchar* str);
SID_EXPORT u64 sid_tstr_parse_u64(const tchar* str);
SID_EXPORT s8 sid_str_parse_s8(const schar* str);
SID_EXPORT s8 sid_wstr_parse_s8(const wchar* str);
SID_EXPORT s8 sid_tstr_parse_s8(const tchar* str);
SID_EXPORT s16 sid_str_parse_s16(const schar* str);
SID_EXPORT s16 sid_wstr_parse_s16(const wchar* str);
SID_EXPORT s16 sid_tstr_parse_s16(const tchar* str);
SID_EXPORT s32 sid_str_parse_s32(const schar* str);
SID_EXPORT s32 sid_wstr_parse_s32(const wchar* str);
SID_EXPORT s32 sid_tstr_parse_s32(const tchar* str);
SID_EXPORT s64 sid_str_parse_s64(const schar* str);
SID_EXPORT s64 sid_wstr_parse_s64(const wchar* str);
SID_EXPORT s64 sid_tstr_parse_s64(const tchar* str);
SID_EXPORT f32 sid_str_parse_f32(const schar* str);
SID_EXPORT f32 sid_wstr_parse_f32(const wchar* str);
SID_EXPORT f32 sid_tstr_parse_f32(const tchar* str);
SID_EXPORT f64 sid_str_parse_f64(const schar* str);
SID_EXPORT f64 sid_wstr_parse_f64(const wchar* str);
SID_EXPORT f64 sid_tstr_parse_f64(const tchar* str);
SID_EXPORT uindex sid_str_parse_uindex(const schar* str);
SID_EXPORT uindex sid_wstr_parse_uindex(const wchar* str);
SID_EXPORT uindex sid_tstr_parse_uindex(const tchar* str);
SID_EXPORT ux sid_str_parse_ux(const schar* str);
SID_EXPORT ux sid_wstr_parse_ux(const wchar* str);
SID_EXPORT ux sid_tstr_parse_ux(const tchar* str);
SID_EXPORT sx sid_str_parse_sx(const schar* str);
SID_EXPORT sx sid_wstr_parse_sx(const wchar* str);
SID_EXPORT sx sid_tstr_parse_sx(const tchar* str);
SID_EXPORT fx sid_str_parse_fx(const schar* str);
SID_EXPORT fx sid_wstr_parse_fx(const wchar* str);
SID_EXPORT fx sid_tstr_parse_fx(const tchar* str);
SID_EXPORT b8 sid_str_parse_b8(const schar* str);
SID_EXPORT b8 sid_wstr_parse_b8(const wchar* str);
SID_EXPORT b8 sid_tstr_parse_b8(const tchar* str);
SID_EXPORT s32 sid_str_parse_string_id(const schar* str);
SID_EXPORT s32 sid_wstr_parse_string_id(const wchar* str);
SID_EXPORT s32 sid_tstr_parse_string_id(const tchar* str);
SID_EXPORT void sid_str_convert_u8(u8 number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_u8(u8 number, wchar* buffer, uindex* out_len);
SID_EXPORT void sid_tstr_convert_u8(u8 number, tchar* buffer, uindex* out_len);
SID_EXPORT void sid_str_convert_u8_secure(u8 number, schar* buffer,
                                          uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_u8_secure(u8 number, wchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_u8_secure(u8 number, tchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_u16(u16 number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_u16(u16 number, wchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_tstr_convert_u16(u16 number, tchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_str_convert_u16_secure(u16 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_u16_secure(u16 number, wchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_u16_secure(u16 number, tchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_u32(u32 number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_u32(u32 number, wchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_tstr_convert_u32(u32 number, tchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_str_convert_u32_secure(u32 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_u32_secure(u32 number, wchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_u32_secure(u32 number, tchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_u64(u64 number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_u64(u64 number, wchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_tstr_convert_u64(u64 number, tchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_str_convert_u64_secure(u64 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_u64_secure(u64 number, wchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_u64_secure(u64 number, tchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_s8(s8 number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_s8(s8 number, wchar* buffer, uindex* out_len);
SID_EXPORT void sid_tstr_convert_s8(s8 number, tchar* buffer, uindex* out_len);
SID_EXPORT void sid_str_convert_s8_secure(s8 number, schar* buffer,
                                          uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_s8_secure(s8 number, wchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_s8_secure(s8 number, tchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_s16(s16 number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_s16(s16 number, wchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_tstr_convert_s16(s16 number, tchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_str_convert_s16_secure(s16 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_s16_secure(s16 number, wchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_s16_secure(s16 number, tchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_s32(s32 number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_s32(s32 number, wchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_tstr_convert_s32(s32 number, tchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_str_convert_s32_secure(s32 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_s32_secure(s32 number, wchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_s32_secure(s32 number, tchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_s64(s64 number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_s64(s64 number, wchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_tstr_convert_s64(s64 number, tchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_str_convert_s64_secure(s64 number, schar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_s64_secure(s64 number, wchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_s64_secure(s64 number, tchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_f32(f32 number, u8 precision, schar* buffer,
                                    uindex* out_len);
SID_EXPORT void sid_wstr_convert_f32(f32 number, u8 precision, wchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_tstr_convert_f32(f32 number, u8 precision, tchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_str_convert_f32_secure(f32 number, u8 precision,
                                           schar* buffer, uindex buffer_len,
                                           uindex* out_len);
SID_EXPORT void sid_wstr_convert_f32_secure(f32 number, u8 precision,
                                            wchar* buffer, uindex buffer_len,
                                            uindex* out_len);
SID_EXPORT void sid_tstr_convert_f32_secure(f32 number, u8 precision,
                                            tchar* buffer, uindex buffer_len,
                                            uindex* out_len);
SID_EXPORT void sid_str_convert_f64(f64 number, u8 precision, schar* buffer,
                                    uindex* out_len);
SID_EXPORT void sid_wstr_convert_f64(f64 number, u8 precision, wchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_tstr_convert_f64(f64 number, u8 precision, tchar* buffer,
                                     uindex* out_len);
SID_EXPORT void sid_str_convert_f64_secure(f64 number, u8 precision,
                                           schar* buffer, uindex buffer_len,
                                           uindex* out_len);
SID_EXPORT void sid_wstr_convert_f64_secure(f64 number, u8 precision,
                                            wchar* buffer, uindex buffer_len,
                                            uindex* out_len);
SID_EXPORT void sid_tstr_convert_f64_secure(f64 number, u8 precision,
                                            tchar* buffer, uindex buffer_len,
                                            uindex* out_len);
SID_EXPORT void sid_str_convert_uindex(uindex number, schar* buffer,
                                       uindex* out_len);
SID_EXPORT void sid_wstr_convert_uindex(uindex number, wchar* buffer,
                                        uindex* out_len);
SID_EXPORT void sid_tstr_convert_uindex(uindex number, tchar* buffer,
                                        uindex* out_len);
SID_EXPORT void sid_str_convert_uindex_secure(uindex number, schar* buffer,
                                              uindex buffer_len,
                                              uindex* out_len);
SID_EXPORT void sid_wstr_convert_uindex_secure(uindex number, wchar* buffer,
                                               uindex buffer_len,
                                               uindex* out_len);
SID_EXPORT void sid_tstr_convert_uindex_secure(uindex number, tchar* buffer,
                                               uindex buffer_len,
                                               uindex* out_len);
SID_EXPORT void sid_str_convert_ux(ux number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_ux(ux number, wchar* buffer, uindex* out_len);
SID_EXPORT void sid_tstr_convert_ux(ux number, tchar* buffer, uindex* out_len);
SID_EXPORT void sid_str_convert_ux_secure(ux number, schar* buffer,
                                          uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_ux_secure(ux number, wchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_ux_secure(ux number, tchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_sx(sx number, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_sx(sx number, wchar* buffer, uindex* out_len);
SID_EXPORT void sid_tstr_convert_sx(sx number, tchar* buffer, uindex* out_len);
SID_EXPORT void sid_str_convert_sx_secure(sx number, schar* buffer,
                                          uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_sx_secure(sx number, wchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_sx_secure(sx number, tchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_fx(fx number, u8 precision, schar* buffer,
                                   uindex* out_len);
SID_EXPORT void sid_wstr_convert_fx(fx number, u8 precision, wchar* buffer,
                                    uindex* out_len);
SID_EXPORT void sid_tstr_convert_fx(fx number, u8 precision, tchar* buffer,
                                    uindex* out_len);
SID_EXPORT void sid_str_convert_fx_secure(fx number, u8 precision,
                                          schar* buffer, uindex buffer_len,
                                          uindex* out_len);
SID_EXPORT void sid_wstr_convert_fx_secure(fx number, u8 precision,
                                           wchar* buffer, uindex buffer_len,
                                           uindex* out_len);
SID_EXPORT void sid_tstr_convert_fx_secure(fx number, u8 precision,
                                           tchar* buffer, uindex buffer_len,
                                           uindex* out_len);
SID_EXPORT void sid_str_convert_b8(b8 boolean, schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_b8(b8 boolean, wchar* buffer, uindex* out_len);
SID_EXPORT void sid_tstr_convert_b8(b8 boolean, tchar* buffer, uindex* out_len);
SID_EXPORT void sid_str_convert_b8_secure(b8 boolean, schar* buffer,
                                          uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_b8_secure(b8 boolean, wchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_b8_secure(b8 boolean, tchar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_str_convert_string_id(sid_string_id string_id,
                                          schar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_string_id(sid_string_id string_id,
                                           wchar* buffer, uindex* out_len);
SID_EXPORT void sid_tstr_convert_string_id(sid_string_id string_id,
                                           tchar* buffer, uindex* out_len);
SID_EXPORT void sid_str_convert_string_id_secure(sid_string_id string_id,
                                                 schar* buffer,
                                                 uindex buffer_len,
                                                 uindex* out_len);
SID_EXPORT void sid_wstr_convert_string_id_secure(sid_string_id string_id,
                                                  wchar* buffer,
                                                  uindex buffer_len,
                                                  uindex* out_len);
SID_EXPORT void sid_tstr_convert_string_id_secure(sid_string_id string_id,
                                                  tchar* buffer,
                                                  uindex buffer_len,
                                                  uindex* out_len);
SID_EXPORT void sid_str_convert_hex(u8 byte, schar* buffer, uindex* out_len);
SID_EXPORT void sid_str_convert_hex_secure(u8 byte, schar* buffer,
                                           uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_wstr_convert_hex(u8 byte, wchar* buffer, uindex* out_len);
SID_EXPORT void sid_wstr_convert_hex_secure(u8 byte, wchar* buffer,
                                            uindex buffer_len, uindex* out_len);
SID_EXPORT void sid_tstr_convert_hex(u8 byte, tchar* buffer, uindex* out_len);
SID_EXPORT void sid_tstr_convert_hex_secure(u8 byte, tchar* buffer,
                                            uindex buffer_len, uindex* out_len);

#endif  // SID_LIB_STRING_H_
