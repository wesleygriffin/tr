#ifndef TR_MATH_POINT3_H_
#define TR_MATH_POINT3_H_

#include "math/detail.h"
#include "math/point.h"

namespace math {

template <>
struct point<float, 3> {
  using V = simd::float32x4;
  using T = float;
  enum { N = 3 };

  union {
    V m{};

    detail::scalar_accessor<T, V, 0> x;
    detail::scalar_accessor<T, V, 1> y;
    detail::scalar_accessor<T, V, 2> z;
  };

  point() noexcept {}
  constexpr point(V v) noexcept
    : m(v) {}

  point(T s) noexcept
    : m(simd::set1<simd::float32x4>(s)) {}
  point(T x, T y, T z, T w = T(0)) noexcept
    : m(simd::set4<simd::float32x4>(x, y, z, w)) {}

  constexpr operator V() const noexcept { return m; }

}; // struct point<float, 3>

static inline point3 const& MATHAPI_CALL operator+(point3 const& p) noexcept {
  return p;
}

static inline point3 MATHAPI_CALL operator-(point3 p) noexcept {
  return simd::neg(p);
}

static inline point3 MATHAPI_CALL operator+=(point3& a, point3 b) noexcept {
  a = simd::add(a, b);
  return a;
}

static inline point3 MATHAPI_CALL operator-=(point3& a, point3 b) noexcept {
  a = simd::sub(a, b);
  return a;
}

static inline point3 MATHAPI_CALL operator*=(point3& a, point3 b) noexcept {
  a = simd::mul(a, b);
  return a;
}

static inline point3 MATHAPI_CALL operator/=(point3& a, point3 b) noexcept {
  a = simd::div(a, b);
  return a;
}

static inline point3 MATHAPI_CALL operator+(point3 a, point3 b) noexcept {
  return simd::add(a, b);
}

static inline point3 MATHAPI_CALL operator+(point3 p, vec3 v) noexcept {
  return simd::add(p, v);
}

static inline vec3 MATHAPI_CALL operator-(point3 a, point3 b) noexcept {
  return simd::sub(a, b);
}

static inline point3 MATHAPI_CALL operator-(point3 p, vec3 v) noexcept {
  return simd::sub(p, v);
}

static inline point3 MATHAPI_CALL operator*(point3 a, point3 b) noexcept {
  return simd::mul(a, b);
}

static inline point3 MATHAPI_CALL operator/(point3 a, point3 b) noexcept {
  return simd::div(a, b);
}

static inline point3 MATHAPI_CALL abs(point3 p) noexcept {
  return simd::abs(p);
}

static inline point3 MATHAPI_CALL min(point3 a, point3 b) noexcept {
  return simd::min(a, b);
}

static inline point3 MATHAPI_CALL max(point3 a, point3 b) noexcept {
  return simd::max(a, b);
}

static inline point3 MATHAPI_CALL clamp(point3 const& p, point3 const& pmin,
                                        point3 const& pmax) noexcept {
  return simd::clamp(p, pmin, pmax);
}

static inline point3 MATHAPI_CALL saturate(point3 p) noexcept {
  return clamp(p, 0.0f, 1.f);
}

static inline point3 MATHAPI_CALL hmin(point3 p) noexcept {
  return simd::hmin(p);
}

static inline point3 MATHAPI_CALL hmax(point3 p) noexcept {
  return simd::hmax(p);
}

static inline point3 MATHAPI_CALL round(point3 p) noexcept {
  return simd::round(p);
}

static inline point3 MATHAPI_CALL floor(point3 p) noexcept {
  return simd::floor(p);
}

static inline point3 MATHAPI_CALL ceil(point3 p) noexcept {
  return simd::ceil(p);
}

static inline point3 MATHAPI_CALL trunc(point3 p) noexcept {
  return simd::trunc(p);
}

} // namespace math

#endif // TR_MATH_POINT3_H_
