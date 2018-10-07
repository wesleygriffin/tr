#ifndef TR_MATH_SCALAR_H_
#define TR_MATH_SCALAR_H_

#include <cmath>

namespace math {

template <class T>
constexpr inline T min(T a, T b) noexcept {
  return (a < b ? a : b);
}

template <class T>
constexpr inline T max(T a, T b) noexcept {
  return (a > b ? a : b);
}

constexpr inline float lerp(float a, float b, float t) noexcept {
  return a + (b - a) * t;
}

} // namespace math

#endif // TR_MATH_SCALAR_H_
