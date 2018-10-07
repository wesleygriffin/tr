#ifndef TR_SIMD_SSE2_INT128_H_
#define TR_SIMD_SSE2_INT128_H_

#include "simd/simd.h"

namespace simd {

static inline __m128i SIMDAPI_CALL _mm_not_si128(__m128i a) noexcept {
  return _mm_xor_si128(a, _mm_cmpeq_epi8(a, a));
}

template <uint32 X, uint32 Y, uint32 Z, uint32 W>
static inline int32x4 SIMDAPI_CALL shuffle(int32x4 v) noexcept {
  static_assert(X < 4 && Y < 4 && Z < 4 && W < 4);
  return _mm_shuffle_epi32(v, _MM_SHUFFLE(W, Z, Y, X));
}

template <>
inline int32x4 SIMDAPI_CALL shuffle<0, 1, 2, 3>(int32x4 v) noexcept {
  return v;
}

template <unsigned int I>
static inline int32x4 SIMDAPI_CALL set_component(int32x4 a, int32 s) noexcept {
  static_assert(I < 4);
  return _mm_insert_epi32(a, s, I);
}

template <unsigned int I>
static inline int32 SIMDAPI_CALL get_component(int32x4 a) noexcept {
  static_assert(I < 4);
  return _mm_extract_epi32(a, Index);
}

template <>
inline int32x4 SIMDAPI_CALL zero<int32x4>() noexcept {
  return _mm_setzero_si128();
}

template <>
inline int32x4 SIMDAPI_CALL set1<int32x4, int32>(int32 s) noexcept {
  return _mm_set1_epi32(s);
}

template <>
inline int32x4 SIMDAPI_CALL set4<int32x4, int32>(int32 x, int32 y, int32 z,
                                                 int32 w) noexcept {
  return _mm_setr_epi32(x, y, z, w);
}

template <>
inline int32x4 SIMDAPI_CALL uload<int32x4, int32>(int32 const* p) noexcept {
  return _mm_loadu_si128(reinterpret_cast<const __m128i*>(p));
}

static inline void SIMDAPI_CALL ustore(int32* p, int32x4 v) noexcept {
  _mm_storeu_si128(reinterpret_cast<__m128i*>(p), v);
}

static inline int32x4 SIMDAPI_CALL unpackhi(int32x4 a,
                                              int32x4 b) noexcept {
  return _mm_unpackhi_epi32(a, b);
}

static inline int32x4 SIMDAPI_CALL unpacklo(int32x4 a,
                                              int32x4 b) noexcept {
  return _mm_unpacklo_epi32(a, b);
}

static inline int32x4 SIMDAPI_CALL bit_nand(int32x4 a,
                                              int32x4 b) noexcept {
  return _mm_andnot_si128(a, b);
}

static inline int32x4 SIMDAPI_CALL bit_and(int32x4 a,
                                             int32x4 b) noexcept {
  return _mm_and_si128(a, b);
}

static inline int32x4 SIMDAPI_CALL bit_or(int32x4 a, int32x4 b) noexcept {
  return _mm_or_si128(a, b);
}

static inline int32x4 SIMDAPI_CALL bit_xor(int32x4 a,
                                             int32x4 b) noexcept {
  return _mm_xor_si128(a, b);
}

static inline int32x4 SIMDAPI_CALL bit_not(int32x4 v) noexcept {
  return _mm_not_si128(v);
}

static inline int32x4 SIMDAPI_CALL min(int32x4 a, int32x4 b) noexcept {
  return _mm_min_epi32(a, b);
}

static inline int32x4 SIMDAPI_CALL max(int32x4 a, int32x4 b) noexcept {
  return _mm_max_epi32(a, b);
}

static inline int32x4 SIMDAPI_CALL abs(int32x4 v) noexcept {
  return _mm_abs_epi32(v);
}

static inline int32x4 SIMDAPI_CALL neg(int32x4 v) noexcept {
  return _mm_sub_epi32(_mm_setzero_si128(), v);
}

static inline int32x4 SIMDAPI_CALL add(int32x4 a, int32x4 b) noexcept {
  return _mm_add_epi32(a, b);
}

static inline int32x4 SIMDAPI_CALL sub(int32x4 a, int32x4 b) noexcept {
  return _mm_sub_epi32(a, b);
}

static inline mask32x4 SIMDAPI_CALL equal_to(int32x4 a, int32x4 b) noexcept {
  return _mm_cmpeq_epi8(a, b);
}

static inline mask32x4 SIMDAPI_CALL not_equal_to(int32x4 a,
                                                 int32x4 b) noexcept {
  return _mm_not_si128(equal_to(b, a));
}

static inline mask32x4 SIMDAPI_CALL greater(int32x4 a, int32x4 b) noexcept {
  __m128i const sign = _mm_set1_epi32(0x80808080);
  return _mm_cmpgt_epi8(_mm_xor_si128(a, sign), _mm_xor_si128(b, sign));
}

static inline mask32x4 SIMDAPI_CALL less(int32x4 a, int32x4 b) noexcept {
  return greater(b, a);
}

static inline mask32x4 SIMDAPI_CALL less_equal(int32x4 a, int32x4 b) noexcept {
  return _mm_not_si128(greater(a, b));
}

static inline mask32x4 SIMDAPI_CALL greater_equal(int32x4 a,
                                                  int32x4 b) noexcept {
  return _mm_not_si128(greater(b, a));
}

static inline int32x4 SIMDAPI_CALL select(mask32x4 mask, int32x4 a,
                                          int32x4 b) noexcept {
  return _mm_or_si128(_mm_and_si128(mask, a), _mm_andnot_si128(mask, b));
}

} // namespace simd

#endif // TR_SIMD_SSE2_INT128_H_
