#ifndef TR_MATH_VEC_H_
#define TR_MATH_VEC_H_

#include "math/types.h"
#include "simd/simd.h"
#include <algorithm>
#include <cmath>

namespace math {

template <class T, int N>
struct vec {
  using V = void;

  T m[N];

  constexpr vec() noexcept = default;

  constexpr T& operator[](int i) noexcept { return m[i]; }
  constexpr T const& operator[](int i) const noexcept { return m[i]; }
}; // struct vec

using vec2 = vec<float, 2>;
using vec3 = vec<float, 3>;
using vec3i = vec<int32, 3>;
using vec4 = vec<float, 4>;

using mask32x4 = simd::mask32x4;

} // namespace math

#include "math/vec3.h"
#include "math/vec3i.h"
#include "math/vec4.h"

#endif // TR_MATH_VEC_H_
