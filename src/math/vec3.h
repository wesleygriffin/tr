#ifndef TR_MATH_VEC3_H_
#define TR_MATH_VEC3_H_

#include "math/detail.h"
#include "math/vec.h"

namespace math {

template <>
struct vec<float, 3> {
  using V = simd::float32x4;
  using T = float;
  enum { N = 3 };

  union {
    V m{};

    detail::scalar_accessor<T, V, 0> x;
    detail::scalar_accessor<T, V, 1> y;
    detail::scalar_accessor<T, V, 2> z;
  };

  vec() noexcept {}
  constexpr vec(V v) noexcept
    : m(v) {}

  vec(T s) noexcept
    : m(simd::set1<simd::float32x4, float>(s)) {}
  vec(T x, T y, T z) noexcept
    : m(simd::set4<simd::float32x4, float>(x, y, z, 0)) {}

  constexpr operator V() const noexcept { return m; }
}; // struct vec<float, 3>

static inline vec3 const& MATHAPI_CALL operator+(vec3 const& v) noexcept {
  return v;
}

static inline vec3 MATHAPI_CALL operator-(vec3 v) noexcept {
  return simd::neg(v);
}

static inline vec3 MATHAPI_CALL operator+=(vec3& a, vec3 b) noexcept {
  a = simd::add(a, b);
  return a;
}

static inline vec3 MATHAPI_CALL operator-=(vec3& a, vec3 b) noexcept {
  a = simd::sub(a, b);
  return a;
}

static inline vec3 MATHAPI_CALL operator*=(vec3& a, vec3 b) noexcept {
  a = simd::mul(a, b);
  return a;
}

static inline vec3 MATHAPI_CALL operator/=(vec3& a, vec3 b) noexcept {
  a = simd::div(a, b);
  return a;
}

static inline vec3 MATHAPI_CALL operator+(vec3 a, vec3 b) noexcept {
  return simd::add(a, b);
}

static inline vec3 MATHAPI_CALL operator-(vec3 a, vec3 b) noexcept {
  return simd::sub(a, b);
}

static inline vec3 MATHAPI_CALL operator*(vec3 a, vec3 b) noexcept {
  return simd::mul(a, b);
}

static inline vec3 MATHAPI_CALL operator/(vec3 a, vec3 b) noexcept {
  return simd::div(a, b);
}

static inline vec3 MATHAPI_CALL abs(vec3 v) noexcept {
  return simd::abs(v);
}

static inline vec3 MATHAPI_CALL square(vec3 v) noexcept {
  return simd::dot3(v, v);
}

static inline vec3 MATHAPI_CALL length(vec3 v) noexcept {
  return simd::sqrt(simd::dot3(v, v));
}

static inline vec3 MATHAPI_CALL normalize(vec3 v) noexcept {
  return simd::normalize(v);
}

static inline vec3 MATHAPI_CALL round(vec3 v) noexcept {
  return simd::round(v);
}

static inline vec3 MATHAPI_CALL floor(vec3 v) noexcept {
  return simd::floor(v);
}

static inline vec3 MATHAPI_CALL ceil(vec3 v) noexcept {
  return simd::ceil(v);
}

static inline vec3 MATHAPI_CALL trunc(vec3 v) noexcept {
  return simd::trunc(v);
}

static inline vec3 MATHAPI_CALL fract(vec3 v) noexcept {
  return simd::fract(v);
}

static inline vec3 MATHAPI_CALL sign(vec3 v) noexcept {
  return simd::sign(v);
}

static inline vec3 MATHAPI_CALL sqrt(vec3 v) noexcept {
  return simd::sqrt(v);
}

static inline vec3 MATHAPI_CALL min(vec3 a, vec3 b) noexcept {
  return simd::min(a, b);
}

static inline vec3 MATHAPI_CALL max(vec3 a, vec3 b) noexcept {
  return simd::max(a, b);
}

static inline vec3 MATHAPI_CALL dot(vec3 a, vec3 b) noexcept {
  return simd::dot3(a, b);
}

static inline vec3 MATHAPI_CALL cross(vec3 a, vec3 b) noexcept {
  return simd::cross3(a, b);
}

static inline vec3 MATHAPI_CALL clamp(vec3 v, vec3 vmin, vec3 vmax) noexcept {
  return simd::clamp(v, vmin, vmax);
}

static inline vec3 MATHAPI_CALL saturate(vec3 v) noexcept {
  return clamp(v, 0.0f, 1.f);
}

static inline vec3 MATHAPI_CALL lerp(vec3 a, vec3 b, vec3 t) noexcept {
  return a + (b - a) * t;
}

static inline vec3 MATHAPI_CALL lerp(vec3 a, vec3 b, float t) noexcept {
  return lerp(a, b, vec3{t});
}

static inline vec3 MATHAPI_CALL hmin(vec3 v) noexcept {
  return simd::hmin(v);
}

static inline vec3 MATHAPI_CALL hmax(vec3 v) noexcept {
  return simd::hmax(v);
}

template <int X, int Y, int Z>
static inline vec3 MATHAPI_CALL shuffle(vec3 a, vec3 b) noexcept {
  return simd::shuffle<X, Y, Z, 3>(a, b);
}

static inline vec3 MATHAPI_CALL operator&(vec3 a, vec3 b) noexcept {
  return simd::bit_and(a, b);
}

static inline vec3 MATHAPI_CALL operator|(vec3 a, vec3 b) noexcept {
  return simd::bit_or(a, b);
}

static inline vec3 MATHAPI_CALL operator^(vec3 a, vec3 b) noexcept {
  return simd::bit_xor(a, b);
}

static inline vec3 MATHAPI_CALL operator~(vec3 v) noexcept {
  return simd::bit_not(v);
}

static inline mask32x4 MATHAPI_CALL operator>(vec3 a, vec3 b) noexcept {
  return simd::greater(a, b);
}

static inline mask32x4 MATHAPI_CALL operator>=(vec3 a, vec3 b) noexcept {
  return simd::greater_equal(a, b);
}

static inline mask32x4 MATHAPI_CALL operator<(vec3 a, vec3 b) noexcept {
  return simd::less(a, b);
}

static inline mask32x4 MATHAPI_CALL operator<=(vec3 a, vec3 b) noexcept {
  return simd::less_equal(a, b);
}

static inline mask32x4 MATHAPI_CALL operator==(vec3 a, vec3 b) noexcept {
  return simd::equal_to(a, b);
}

static inline mask32x4 MATHAPI_CALL operator!=(vec3 a, vec3 b) noexcept {
  return simd::not_equal_to(a, b);
}

static inline vec3 MATHAPI_CALL select(mask32x4 mask, vec3 a, vec3 b) noexcept {
  return simd::select(mask, a, b);
}

} // namespace math

#endif // TR_MATH_VEC3_H_
