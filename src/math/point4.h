#ifndef TR_MATH_POINT3_H_
#define TR_MATH_POINT3_H_

#include "math/point.h"

namespace math {

template <>
struct point<float, 4> {
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

  constexpr point() noexcept = default;
  constexpr point(V v) noexcept
    : m(v) {}

  constexpr point(T s) noexcept
    : m(simd::set1<simd::float32x4>(s)) {}
  constexpr point(T x, T y, T z, T w = T(1)) noexcept
    : m(simd::set4<simd::float32x4>(x, y, z, w)) {}

  constexpr operator V() const noexcept { return m; }
}; // struct point<float, 4>

static inline point4 const& MATHAPI_CALL operator+(point4 const& p) noexcept {
  return p;
}

static inline point4 MATHAPI_CALL operator-(point4 const& p) noexcept {
  return simd::neg(p);
}

static inline point4 MATHAPI_CALL operator+=(point4& a, point4 b) noexcept {
  a = simd::add(a, b);
  return a;
}

static inline point4 MATHAPI_CALL operator-=(point4& a, point4 b) noexcept {
  a = simd::sub(a, b);
  return a;
}

static inline point4 MATHAPI_CALL operator*=(point4& a, point4 b) noexcept {
  a = simd::mul(a, b);
  return a;
}

static inline point4 MATHAPI_CALL operator/=(point4& a, point4 b) noexcept {
  a = simd::div(a, b);
  return a;
}

static inline point4 MATHAPI_CALL operator+(point4 a, point4 b) noexcept {
  return simd::add(a, b);
}

static inline point4 MATHAPI_CALL operator+(point4 p, vec4 v) noexcept {
  return simd::add(p, v);
}

static inline vec4 MATHAPI_CALL operator-(point4 a, point4 b) noexcept {
  return simd::sub(a, b);
}

static inline point4 MATHAPI_CALL operator-(point4 p, vec4 v) noexcept {
  return simd::sub(p, v);
}

static inline point4 MATHAPI_CALL operator*(point4 a, point4 b) noexcept {
  return simd::mul(a, b);
}

static inline point4 MATHAPI_CALL operator/(point4 a, point4 b) noexcept {
  return simd::div(a, b);
}

static inline point4 MATHAPI_CALL abs(point4 p) noexcept {
  return simd::abs(p);
}

static inline point4 MATHAPI_CALL min(point4 a, point4 b) noexcept {
  return simd::min(a, b);
}

static inline point4 MATHAPI_CALL max(point4 a, point4 b) noexcept {
  return simd::max(a, b);
}

static inline point4 MATHAPI_CALL clamp(point4 const& p, point4 const& pmin,
                                        point4 const& pmax) noexcept {
  return simd::clamp(p, pmin, pmax);
}

static inline point4 MATHAPI_CALL saturate(point4 p) noexcept {
  return clamp(p, 0.0f, 1.f);
}

static inline point4 MATHAPI_CALL lerp(point4 const& a, point4 const& b,
                                       point4 const& t) noexcept {
  math::vec4 const v = b - a;
  return a + math::point4(v.x, v.y, v.z, v.w) * t;
}

static inline point4 MATHAPI_CALL hmin(point4 p) noexcept {
  return simd::hmin(p);
}

static inline point4 MATHAPI_CALL hmax(point4 p) noexcept {
  return simd::hmax(p);
}

} // namespace math

#endif // TR_MATH_POINT3_H_
