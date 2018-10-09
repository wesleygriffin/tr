#ifndef TR_MATH_RAY_H_
#define TR_MATH_RAY_H_

#include "math/point3.h"
#include "math/vec3.h"

namespace math {

struct ray {
  point3 origin{};
  vec3 direction{};
  float time{0.f};

  ray() noexcept = default;
  constexpr ray(point3 o, vec3 d, float t = 0.f) noexcept
    : origin(o)
    , direction(d)
    , time(t){};

  point3 point_at(float t) const noexcept { return origin + direction * t; }
}; // struct ray

} // namespace math

#endif // TR_MATH_RAY_H_
