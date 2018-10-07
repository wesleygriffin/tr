#ifndef TR_MATH_POINT_H_
#define TR_MATH_POINT_H_

#include "math/types.h"
#include "math/vec.h"
#include "simd/simd.h"
#include <algorithm>
#include <cmath>

namespace math {

template <class T, int N>
struct point {
  using V = void;

  T m[N];

  constexpr point() noexcept = default;

  constexpr T& operator[](int i) noexcept { return m[i]; }
  constexpr T const& operator[](int i) const noexcept { return m[i]; }
}; // struct point

using point3 = point<float, 3>;
using point4 = point<float, 4>;

} // namespace math

#include "math/point3.h"
#include "math/point4.h"

#endif // TR_MATH_POINT_H_
