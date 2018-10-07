#ifndef TR_MATH_VEC3I_H_
#define TR_MATH_VEC3I_H_

#include "math/detail.h"
#include "math/vec.h"
#include "math/vec3.h"

namespace math {

template <>
struct vec<int32, 3> {
  using V = simd::int32x4;
  using T = int32;
  enum { N = 3 };

  union {
    V m;

    detail::scalar_accessor<T, V, 0> x;
    detail::scalar_accessor<T, V, 1> y;
    detail::scalar_accessor<T, V, 2> z;
  };

  constexpr vec() noexcept = default;
  constexpr vec(V v) noexcept
    : m(v) {}

  constexpr vec(T s) noexcept
    : m(simd::set1<simd::int32x4>(s)) {}
  constexpr vec(T x, T y, T z) noexcept
    : m(simd::set4<simd::int32x4, int32>(x, y, z, 0)) {}

  constexpr vec(vec3 v) noexcept
    : m(simd::set4<simd::int32x4>(int32(v.x), int32(v.y), int32(v.z), 0)) {}

  constexpr operator V() const noexcept { return m; }
}; // struct vec<int, 3>

static inline vec3i const& MATHAPI_CALL operator+(vec3i const& v) noexcept {
  return v;
}

static inline vec3i MATHAPI_CALL operator-(vec3i v) noexcept {
  return simd::neg(v);
}

static inline vec3i MATHAPI_CALL operator+=(vec3i& a, vec3i b) noexcept {
  a = simd::add(a, b);
  return a;
}

static inline vec3i MATHAPI_CALL operator-=(vec3i& a, vec3i b) noexcept {
  a = simd::sub(a, b);
  return a;
}

static inline vec3i MATHAPI_CALL operator+(vec3i a, vec3i b) noexcept {
  return simd::add(a, b);
}

static inline vec3i MATHAPI_CALL operator-(vec3i a, vec3i b) noexcept {
  return simd::sub(a, b);
}

static inline vec3i MATHAPI_CALL abs(vec3i v) noexcept {
  return simd::abs(v);
}

static inline vec3i MATHAPI_CALL min(vec3i a, vec3i b) noexcept {
  return simd::min(a, b);
}

static inline vec3i MATHAPI_CALL max(vec3i a, vec3i b) noexcept {
  return simd::max(a, b);
}

template <int X, int Y, int Z>
static inline vec3i MATHAPI_CALL shuffle(vec3i a, vec3i b) noexcept {
  return simd::shuffle<X, Y, Z, 3>(a, b);
}

static inline vec3i MATHAPI_CALL operator&(vec3i a, vec3i b) noexcept {
  return simd::bit_and(a, b);
}

static inline vec3i MATHAPI_CALL operator|(vec3i a, vec3i b) noexcept {
  return simd::bit_or(a, b);
}

static inline vec3i MATHAPI_CALL operator^(vec3i a, vec3i b) noexcept {
  return simd::bit_xor(a, b);
}

static inline vec3i MATHAPI_CALL operator~(vec3i v) noexcept {
  return simd::bit_not(v);
}

static inline mask32x4 MATHAPI_CALL operator>(vec3i a, vec3i b) noexcept {
  return simd::greater(a, b);
}

static inline mask32x4 MATHAPI_CALL operator>=(vec3i a, vec3i b) noexcept {
  return simd::greater_equal(a, b);
}

static inline mask32x4 MATHAPI_CALL operator<(vec3i a, vec3i b) noexcept {
  return simd::less(a, b);
}

static inline mask32x4 MATHAPI_CALL operator<=(vec3i a, vec3i b) noexcept {
  return simd::less_equal(a, b);
}

static inline mask32x4 MATHAPI_CALL operator==(vec3i a, vec3i b) noexcept {
  return simd::equal_to(a, b);
}

static inline mask32x4 MATHAPI_CALL operator!=(vec3i a, vec3i b) noexcept {
  return simd::not_equal_to(a, b);
}

static inline vec3i MATHAPI_CALL select(mask32x4 mask, vec3i a, vec3i b) noexcept {
  return simd::select(mask, a, b);
}

} // namespace math

#endif // TR_MATH_VEC3I_H_
