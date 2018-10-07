#ifndef TR_SIMD_SSE2_FLOAT128_H_
#define TR_SIMD_SSE2_FLOAT128_H_

#include "simd/simd.h"

namespace simd {

template <int X, int Y, int Z, int W>
static inline float32x4 SIMDAPI_CALL shuffle(float32x4 a,
                                             float32x4 b) noexcept {
  static_assert(X < 4 && Y < 4 && Z < 4 && W < 4);
  return _mm_shuffle_ps(a, b, _MM_SHUFFLE(W, Z, Y, X));
}

template <int X, int Y, int Z, int W>
static inline float32x4 SIMDAPI_CALL shuffle(float32x4 v) noexcept {
  static_assert(X < 4 && Y < 4 && Z < 4 && W < 4);
  return _mm_shuffle_ps(v, v, _MM_SHUFFLE(W, Z, Y, X));
}

template <>
inline float32x4 SIMDAPI_CALL shuffle<0, 1, 2, 3>(float32x4 v) noexcept {
  return v;
}

template <int I>
static inline float32x4 SIMDAPI_CALL set_component(float32x4 v,
                                                   float s) noexcept {
  static_assert(I < 4);
  return _mm_insert_ps(v, _mm_set_ss(s), I * 0x10);
}

template <int I>
float SIMDAPI_CALL get_component(float32x4 v) noexcept;

template <>
inline float SIMDAPI_CALL get_component<0>(float32x4 v) noexcept {
  return _mm_cvtss_f32(v);
}

template <>
inline float SIMDAPI_CALL get_component<1>(float32x4 v) noexcept {
  return _mm_cvtss_f32(shuffle<1, 1, 1, 1>(v));
}

template <>
inline float SIMDAPI_CALL get_component<2>(float32x4 v) noexcept {
  return _mm_cvtss_f32(shuffle<2, 2, 2, 2>(v));
}

template <>
inline float SIMDAPI_CALL get_component<3>(float32x4 v) noexcept {
  return _mm_cvtss_f32(shuffle<3, 3, 3, 3>(v));
}

template <>
inline float32x4 SIMDAPI_CALL zero<float32x4>() noexcept {
  return _mm_setzero_ps();
}

template <>
inline float32x4 SIMDAPI_CALL set1<float32x4>(float s) noexcept {
  return _mm_set1_ps(s);
}

template <>
inline float32x4 SIMDAPI_CALL set4<float32x4>(float x, float y, float z,
                                              float w) noexcept {
  return _mm_setr_ps(x, y, z, w);
}

template <>
inline float32x4 SIMDAPI_CALL uload<float32x4>(float const* p) noexcept {
  return _mm_loadu_ps(p);
}

static inline void SIMDAPI_CALL ustore(float* p, float32x4 v) noexcept {
  _mm_storeu_ps(p, v);
}

static inline float32x4 SIMDAPI_CALL movelh(float32x4 a, float32x4 b) noexcept {
  return _mm_movelh_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL movehl(float32x4 a, float32x4 b) noexcept {
  return _mm_movehl_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL unpackhi(float32x4 a,
                                              float32x4 b) noexcept {
  return _mm_unpackhi_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL unpacklo(float32x4 a,
                                              float32x4 b) noexcept {
  return _mm_unpacklo_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL bit_nand(float32x4 a,
                                              float32x4 b) noexcept {
  return _mm_andnot_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL bit_and(float32x4 a,
                                             float32x4 b) noexcept {
  return _mm_and_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL bit_or(float32x4 a, float32x4 b) noexcept {
  return _mm_or_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL bit_xor(float32x4 a,
                                             float32x4 b) noexcept {
  return _mm_xor_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL bit_not(float32x4 v) noexcept {
  return _mm_xor_ps(v, _mm_cmpeq_ps(v, v));
}

static inline float32x4 SIMDAPI_CALL min(float32x4 a, float32x4 b) noexcept {
  return _mm_min_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL max(float32x4 a, float32x4 b) noexcept {
  return _mm_max_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL hmin(float32x4 v) noexcept {
  __m128 tmp = _mm_min_ps(v, _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1)));
  return _mm_min_ps(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
}

static inline float32x4 SIMDAPI_CALL hmax(float32x4 v) noexcept {
  __m128 tmp = _mm_max_ps(v, _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1)));
  return _mm_max_ps(tmp, _mm_shuffle_ps(tmp, tmp, _MM_SHUFFLE(1, 0, 3, 2)));
}

static inline float32x4 SIMDAPI_CALL abs(float32x4 v) noexcept {
  return _mm_max_ps(v, _mm_sub_ps(_mm_setzero_ps(), v));
}

static inline float32x4 SIMDAPI_CALL neg(float32x4 v) noexcept {
  return _mm_sub_ps(_mm_setzero_ps(), v);
}

static inline float32x4 SIMDAPI_CALL sign(float32x4 v) noexcept {
  __m128 sign_mask = _mm_set1_ps(-0.0f);
  __m128 value_mask = _mm_cmpeq_ps(v, _mm_setzero_ps());
  __m128 sign_bits = _mm_and_ps(v, sign_mask);
  __m128 value_bits = _mm_and_ps(value_mask, _mm_set1_ps(1.0f));
  return _mm_or_ps(value_bits, sign_bits);
}

static inline float32x4 SIMDAPI_CALL add(float32x4 a, float32x4 b) noexcept {
  return _mm_add_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL sub(float32x4 a, float32x4 b) noexcept {
  return _mm_sub_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL mul(float32x4 a, float32x4 b) noexcept {
  return _mm_mul_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL div(float32x4 a, float32x4 b) noexcept {
  return _mm_div_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL div(float32x4 a, float s) noexcept {
  return _mm_div_ps(a, _mm_set1_ps(s));
}

static inline float32x4 SIMDAPI_CALL hadd(float32x4 a, float32x4 b) noexcept {
  return _mm_hadd_ps(a, b);
}

static inline float32x4 SIMDAPI_CALL madd(float32x4 a, float32x4 b,
                                          float32x4 c) noexcept {
  // a + b * c
  return _mm_fmadd_ps(b, c, a);
}

static inline float32x4 SIMDAPI_CALL msub(float32x4 a, float32x4 b,
                                          float32x4 c) noexcept {
  // a - b * c
  return _mm_fnmadd_ps(b, c, a);
}

static inline float32x4 SIMDAPI_CALL fast_rcp(float32x4 v) noexcept {
  return _mm_rcp_ps(v);
}

static inline float32x4 SIMDAPI_CALL fast_rsqrt(float32x4 v) noexcept {
  return _mm_rsqrt_ps(v);
}

static inline float32x4 SIMDAPI_CALL fast_sqrt(float32x4 v) noexcept {
  float32x4 n = _mm_rsqrt_ps(v);
  return _mm_mul_ps(v, n);
}

static inline float32x4 SIMDAPI_CALL rcp(float32x4 v) noexcept {
  float32x4 n = _mm_rcp_ps(v);
  float32x4 m = _mm_mul_ps(_mm_mul_ps(n, n), v);
  return _mm_sub_ps(_mm_add_ps(n, n), m);
}

static inline float32x4 SIMDAPI_CALL rsqrt(float32x4 v) noexcept {
  float32x4 n = _mm_rsqrt_ps(v);
  float32x4 e = _mm_mul_ps(_mm_mul_ps(n, n), v);
  n = _mm_mul_ps(_mm_set_ps1(0.5f), n);
  e = _mm_sub_ps(_mm_set_ps1(3.0f), e);
  return _mm_mul_ps(n, e);
}

static inline float32x4 SIMDAPI_CALL sqrt(float32x4 v) noexcept {
  return _mm_sqrt_ps(v);
}

static inline float32x4 SIMDAPI_CALL dot3(float32x4 a, float32x4 b) noexcept {
  return _mm_dp_ps(a, b, 0x7f);
}

static inline float32x4 SIMDAPI_CALL dot4(float32x4 a, float32x4 b) noexcept {
  return _mm_dp_ps(a, b, 0xff);
}

static inline float32x4 SIMDAPI_CALL square(float32x4 v) noexcept {
  return dot4(v, v);
}

static inline float32x4 SIMDAPI_CALL length(float32x4 v) noexcept {
  return sqrt(square(v));
}

static inline float32x4 SIMDAPI_CALL normalize(float32x4 v) noexcept {
  return mul(v, rsqrt(square(v)));
}

static inline float32x4 SIMDAPI_CALL clamp(float32x4 v, float32x4 vmin,
                                           float32x4 vmax) noexcept {
  return min(vmax, max(vmin, v));
}

static inline float32x4 SIMDAPI_CALL cross3(float32x4 a, float32x4 b) noexcept {
  float32x4 c = _mm_sub_ps(_mm_mul_ps(a, shuffle<1, 2, 0, 3>(b)),
                           _mm_mul_ps(b, shuffle<1, 2, 0, 3>(a)));
  return shuffle<1, 2, 0, 3>(c);
}

static inline mask32x4 SIMDAPI_CALL not_equal_to(float32x4 a,
                                                 float32x4 b) noexcept {
  return _mm_castps_si128(_mm_cmpneq_ps(a, b));
}

static inline mask32x4 SIMDAPI_CALL equal_to(float32x4 a,
                                             float32x4 b) noexcept {
  return _mm_castps_si128(_mm_cmpeq_ps(a, b));
}

static inline mask32x4 SIMDAPI_CALL less(float32x4 a, float32x4 b) noexcept {
  return _mm_castps_si128(_mm_cmplt_ps(a, b));
}

static inline mask32x4 SIMDAPI_CALL less_equal(float32x4 a,
                                               float32x4 b) noexcept {
  return _mm_castps_si128(_mm_cmple_ps(a, b));
}

static inline mask32x4 SIMDAPI_CALL greater(float32x4 a, float32x4 b) noexcept {
  return _mm_castps_si128(_mm_cmpgt_ps(a, b));
}

static inline mask32x4 SIMDAPI_CALL greater_equal(float32x4 a,
                                                  float32x4 b) noexcept {
  return _mm_castps_si128(_mm_cmpge_ps(a, b));
}

static inline float32x4 SIMDAPI_CALL select(mask32x4 mask, float32x4 a,
                                            float32x4 b) noexcept {
  return _mm_blendv_ps(b, a, _mm_castsi128_ps(mask));
}

static inline float32x4 SIMDAPI_CALL round(float32x4 v) noexcept {
  return _mm_round_ps(v, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
}

static inline float32x4 SIMDAPI_CALL trunc(float32x4 v) noexcept {
  return _mm_round_ps(v, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}

static inline float32x4 SIMDAPI_CALL floor(float32x4 v) noexcept {
  return _mm_round_ps(v, _MM_FROUND_TO_NEG_INF | _MM_FROUND_NO_EXC);
}

static inline float32x4 SIMDAPI_CALL ceil(float32x4 v) noexcept {
  return _mm_round_ps(v, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
}

static inline float32x4 SIMDAPI_CALL fract(float32x4 v) noexcept {
  return sub(v, floor(v));
}

} // namespace simd

#endif // TR_SIMD_SSE2_FLOAT128_H_
