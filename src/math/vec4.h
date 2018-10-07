#ifndef TR_MATH_VEC4_H_
#define TR_MATH_VEC4_H_

#include "math/detail.h"
#include "math/vec.h"

namespace math {

template <>
struct vec<float, 4> {
  using V = simd::float32x4;
  using T = float;
  enum { N = 4 };

  union {
    V m;

    detail::scalar_accessor<T, V, 0> x;
    detail::scalar_accessor<T, V, 1> y;
    detail::scalar_accessor<T, V, 2> z;
    detail::scalar_accessor<T, V, 3> w;
  };

  constexpr vec() noexcept = default;
  constexpr vec(V v) noexcept
    : m(v) {}

  constexpr vec(T s) noexcept
    : m(simd::set1<simd::float32x4>(s)) {}
  constexpr vec(T x, T y, T z, T w = T(0)) noexcept
    : m(simd::set4<simd::float32x4>(x, y, z, w)) {}

  constexpr operator V() const noexcept { return m; }
}; // struct vec<float, 4>

static inline vec4 const& MATHAPI_CALL operator+(vec4 const& v) noexcept {
  return v;
}

static inline vec4 MATHAPI_CALL operator-(vec4 v) noexcept {
  return simd::neg(v);
}

static inline vec4 MATHAPI_CALL operator+=(vec4& a, vec4 b) noexcept {
  a = simd::add(a, b);
  return a;
}

static inline vec4 MATHAPI_CALL operator-=(vec4& a, vec4 b) noexcept {
  a = simd::sub(a, b);
  return a;
}

static inline vec4 MATHAPI_CALL operator*=(vec4& a, vec4 b) noexcept {
  a = simd::mul(a, b);
  return a;
}

static inline vec4 MATHAPI_CALL operator/=(vec4& a, vec4 b) noexcept {
  a = simd::div(a, b);
  return a;
}

static inline vec4 MATHAPI_CALL operator+(vec4 a, vec4 b) noexcept {
  return simd::add(a, b);
}

static inline vec4 MATHAPI_CALL operator-(vec4 a, vec4 b) noexcept {
  return simd::sub(a, b);
}

static inline vec4 MATHAPI_CALL operator*(vec4 a, vec4 b) noexcept {
  return simd::mul(a, b);
}

static inline vec4 MATHAPI_CALL operator/(vec4 a, vec4 b) noexcept {
  return simd::div(a, b);
}

static inline vec4 MATHAPI_CALL abs(vec4 v) noexcept {
  return simd::abs(v);
}

static inline vec4 MATHAPI_CALL square(vec4 v) noexcept {
  return simd::square(v);
}

static inline vec4 MATHAPI_CALL length(vec4 v) noexcept {
  return simd::length(v);
}

static inline vec4 MATHAPI_CALL normalize(vec4 v) noexcept {
  return simd::normalize(v);
}

static inline vec4 MATHAPI_CALL sqrt(vec4 v) noexcept {
  return simd::sqrt(v);
}

static inline vec4 MATHAPI_CALL min(vec4 a, vec4 b) noexcept {
  return simd::min(a, b);
}

static inline vec4 MATHAPI_CALL max(vec4 a, vec4 b) noexcept {
  return simd::max(a, b);
}

static inline vec4 MATHAPI_CALL dot(vec4 a, vec4 b) noexcept {
  return simd::dot4(a, b);
}

static inline vec4 MATHAPI_CALL clamp(vec4 v, vec4 vmin, vec4 vmax) noexcept {
  return simd::clamp(v, vmin, vmax);
}

static inline vec4 MATHAPI_CALL saturate(vec4 v) noexcept {
  return clamp(v, 0.0f, 1.0f);
}

static inline vec4 MATHAPI_CALL lerp(vec4 a, vec4 b, vec4 t) noexcept {
  return a + (b - a) * t;
}

static inline vec4 MATHAPI_CALL lerp(vec4 a, vec4 b, float t) noexcept {
  return lerp(a, b, vec4{t});
}

static inline vec4 MATHAPI_CALL hmin(vec4 v) noexcept {
  return simd::hmin(v);
}

static inline vec4 MATHAPI_CALL hmax(vec4 v) noexcept {
  return simd::hmax(v);
}

template <int X, int Y, int Z, int W>
inline vec4 MATHAPI_CALL shuffle(vec4 a, vec4 b) noexcept {
  return simd::shuffle<X, Y, Z, W>(a, b);
}

static inline vec4 MATHAPI_CALL operator&(vec4 a, vec4 b) noexcept {
  return simd::bit_and(a, b);
}

static inline vec4 MATHAPI_CALL operator|(vec4 a, vec4 b) noexcept {
  return simd::bit_or(a, b);
}

static inline vec4 MATHAPI_CALL operator^(vec4 a, vec4 b) noexcept {
  return simd::bit_xor(a, b);
}

static inline vec4 MATHAPI_CALL operator~(vec4 v) noexcept {
  return simd::bit_not(v);
}

static inline mask32x4 MATHAPI_CALL operator>(vec4 a, vec4 b) noexcept {
  return simd::greater(a, b);
}

static inline mask32x4 MATHAPI_CALL operator>=(vec4 a, vec4 b) noexcept {
  return simd::greater_equal(a, b);
}

static inline mask32x4 MATHAPI_CALL operator<(vec4 a, vec4 b) noexcept {
  return simd::less(a, b);
}

static inline mask32x4 MATHAPI_CALL operator<=(vec4 a, vec4 b) noexcept {
  return simd::less_equal(a, b);
}

static inline mask32x4 MATHAPI_CALL operator==(vec4 a, vec4 b) noexcept {
  return simd::equal_to(a, b);
}

static inline mask32x4 MATHAPI_CALL operator!=(vec4 a, vec4 b) noexcept {
  return simd::not_equal_to(a, b);
}

static inline vec4 MATHAPI_CALL select(mask32x4 mask, vec4 a, vec4 b) noexcept {
  return simd::select(mask, a, b);
}

} // namespace math

#endif // TR_MATH_VEC4_H_
