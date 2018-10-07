#ifndef TR_MATH_COLOR_H_
#define TR_MATH_COLOR_H_

#include "math/types.h"
#include "simd/simd.h"
#include <algorithm>
#include <cmath>

namespace math {

template <class T, int N>
struct color {
  using V = void;

  T m[N];

  constexpr color() noexcept = default;

  constexpr T& operator[](int i) noexcept { return m[i]; }
  constexpr T const& operator[](int i) const noexcept { return m[i]; }
}; // struct color

using color4 = color<float, 4>;

} // namespace math

#include "math/color4.h"

#endif // TR_MATH_COLOR_H_
