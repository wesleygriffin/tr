#ifndef TR_MATH_VEC2_H_
#define TR_MATH_VEC2_H_

#include "math/scalar.h"
#include "math/vec.h"

namespace math {

template <>
struct vec<float, 2> {
  using V = void;
  using T = float;
  enum { N = 2 };

  union {
    struct { T x, y; };
    T m[N];
  };

  vec() noexcept : x(T(0)), y(T(0)) {}

  constexpr vec(T s) noexcept
    : x(s), y(s) {}
  constexpr vec(T x_, T y_) noexcept
    : x(x_), y(y_) {}
}; // struct vec<float, 2>

static inline vec2 const& MATHAPI_CALL operator+(vec2 const& v) noexcept {
  return v;
}

static inline vec2 MATHAPI_CALL operator-(vec2 v) noexcept {
  return {-v.x, -v.y};
}

static inline vec2 MATHAPI_CALL operator+=(vec2& a, vec2 b) noexcept {
  a.x += b.x;
  a.y += b.y;
  return a;
}

static inline vec2 MATHAPI_CALL operator-=(vec2& a, vec2 b) noexcept {
  a.x -= b.x;
  a.y -= b.y;
  return a;
}

static inline vec2 MATHAPI_CALL operator*=(vec2& a, vec2 b) noexcept {
  a.x *= b.x;
  a.y *= b.y;
  return a;
}

static inline vec2 MATHAPI_CALL operator/=(vec2& a, vec2 b) noexcept {
  a.x /= b.x;
  a.y /= b.y;
  return a;
}

static inline vec2 MATHAPI_CALL operator+(vec2 a, vec2 b) noexcept {
  float const x = a.x + b.x;
  float const y = a.y + b.y;
  return {x, y};
}

static inline vec2 MATHAPI_CALL operator-(vec2 a, vec2 b) noexcept {
  float const x = a.x - b.x;
  float const y = a.y - b.y;
  return {x, y};
}

static inline vec2 MATHAPI_CALL operator*(vec2 a, vec2 b) noexcept {
  float const x = a.x * b.x;
  float const y = a.y * b.y;
  return {x, y};
}

static inline vec2 MATHAPI_CALL operator/(vec2 a, vec2 b) noexcept {
  float const x = a.x / b.x;
  float const y = a.y / b.y;
  return {x, y};
}

static inline vec2 MATHAPI_CALL abs(vec2 v) noexcept {
  float const x = std::abs(v.x);
  float const y = std::abs(v.y);
  return {x, y};
}

static inline float MATHAPI_CALL square(vec2 v) noexcept {
  return v.x * v.x + v.y * v.y;
}

static inline float MATHAPI_CALL length(vec2 v) noexcept {
  return std::sqrt(square(v));
}

static inline vec2 MATHAPI_CALL normalize(vec2 v) noexcept {
  return v / length(v);
}

static inline vec2 MATHAPI_CALL sqrt(vec2 v) noexcept {
  float const x = std::sqrt(v.x);
  float const y = std::sqrt(v.y);
  return {x, y};
}

static inline vec2 MATHAPI_CALL min(vec2 a, vec2 b) noexcept {
  float const x = min(a.x, b.x);
  float const y = min(a.y, b.y);
  return {x, y};
}

static inline vec2 MATHAPI_CALL max(vec2 a, vec2 b) noexcept {
  float const x = max(a.x, b.x);
  float const y = max(a.y, b.y);
  return {x, y};
}

static inline float MATHAPI_CALL dot(vec2 a, vec2 b) noexcept {
  return a.x * b.x + a.y * b.y;
}

static inline vec2 MATHAPI_CALL clamp(vec2 const& v, vec2 const& vmin,
                                      vec2 const& vmax) noexcept {
  float const x = max(vmin.x, min(vmax.x, v.x));
  float const y = max(vmin.y, min(vmax.y, v.y));
  return {x, y};
}

static inline vec2 MATHAPI_CALL saturate(vec2 v) noexcept {
  return clamp(v, 0.0f, 1.f);
}

static inline vec2 MATHAPI_CALL lerp(vec2 const& a, vec2 const& b,
                                     vec2 const& t) noexcept {
  float const x = a.x + (b.x - a.x) * t.x;
  float const y = a.y + (b.y - a.y) * t.y;
  return {x, y};
}

static inline vec2 MATHAPI_CALL lerp(vec2 const& a, vec2 const& b,
                                     float t) noexcept {
  return lerp(a, b, vec2{t});
}

static inline vec2 MATHAPI_CALL hmin(vec2 v) noexcept {
  float const s = min(v.x, v.y);
  return {s, s};
}

static inline vec2 MATHAPI_CALL hmax(vec2 v) noexcept {
  float const s = max(v.x, v.y);
  return {s, s};
}

} // namespace math

#endif // TR_MATH_VEC3_H_
