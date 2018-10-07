#ifndef TR_MATH_COLOR4_H_
#define TR_MATH_COLOR4_H_

#include "math/color.h"
#include "math/detail.h"
#include "math/scalar.h"

namespace math {

template <>
struct color<float, 4> {
  using V = simd::float32x4;
  using T = float;
  enum { N = 4 };

  union {
    V m;

    detail::scalar_accessor<T, V, 0> r;
    detail::scalar_accessor<T, V, 1> g;
    detail::scalar_accessor<T, V, 2> b;
    detail::scalar_accessor<T, V, 3> a;
  };

  constexpr color() noexcept = default;
  constexpr color(V v) noexcept
    : m(v) {}

  constexpr color(T s) noexcept
    : m(simd::set1<simd::float32x4>(s)) {}
  constexpr color(T r, T g, T b, T a) noexcept
    : m(simd::set4<simd::float32x4>(r, g, b, a)) {}

  constexpr operator V() const noexcept { return m; }
}; // struct color<float, 4>

static inline color4 const& MATHAPI_CALL operator+(color4 const& c) noexcept {
  return c;
}

static inline color4 MATHAPI_CALL operator-(color4 c) noexcept {
  return simd::neg(c);
}

static inline color4 MATHAPI_CALL operator+=(color4& a, color4 b) noexcept {
  a = simd::add(a, b);
  return a;
}

static inline color4 MATHAPI_CALL operator-=(color4& a, color4 b) noexcept {
  a = simd::sub(a, b);
  return a;
}

static inline color4 MATHAPI_CALL operator*=(color4& a, color4 b) noexcept {
  a = simd::mul(a, b);
  return a;
}

static inline color4 MATHAPI_CALL operator/=(color4& a, color4 b) noexcept {
  a = simd::div(a, b);
  return a;
}

static inline color4 MATHAPI_CALL operator/=(color4& a, float s) noexcept {
  a = simd::div(a, s);
  return a;
}

static inline color4 MATHAPI_CALL operator+(color4 a, color4 b) noexcept {
  return simd::add(a, b);
}

static inline color4 MATHAPI_CALL operator-(color4 a, color4 b) noexcept {
  return simd::sub(a, b);
}

static inline color4 MATHAPI_CALL operator*(color4 a, color4 b) noexcept {
  return simd::mul(a, b);
}

static inline color4 MATHAPI_CALL operator/(color4 a, color4 b) noexcept {
  return simd::div(a, b);
}

static inline color4 MATHAPI_CALL abs(color4 c) noexcept {
  return simd::abs(c);
}

static inline color4 MATHAPI_CALL sqrt(color4 c) noexcept {
  return simd::sqrt(c);
}

static inline color4 MATHAPI_CALL min(color4 a, color4 b) noexcept {
  return simd::min(a, b);
}

static inline color4 MATHAPI_CALL max(color4 a, color4 b) noexcept {
  return simd::max(a, b);
}

static inline color4 MATHAPI_CALL clamp(color4 c, color4 cmin,
                                        color4 cmax) noexcept {
  return simd::clamp(c, cmin, cmax);
}

static inline color4 MATHAPI_CALL saturate(color4 c) noexcept {
  return clamp(c, 0.0f, 1.f);
}

static inline color4 MATHAPI_CALL lerp(color4 a, color4 b, color4 t) noexcept {
  return a + (b - a) * t;
}

static inline color4 MATHAPI_CALL lerp(color4 a, color4 b, float t) noexcept {
  return lerp(a, b, color4{t});
}

static inline color4 MATHAPI_CALL hmin(color4 c) noexcept {
  return simd::hmin(c);
}

static inline color4 MATHAPI_CALL hmax(color4 c) noexcept {
  return simd::hmax(c);
}

} // namespace math

#endif // TR_MATH_COLOR4_H_
