#ifndef TR_MATH_AABB_H_
#define TR_MATH_AABB_H_

#include "math/point.h"
#include "math/ray.h"
#include "math/scalar.h"
#include "math/vec3.h"

namespace math {

struct aabb {
  point3 min{};
  point3 max{};

  constexpr aabb() noexcept = default;
  constexpr aabb(point3 min_, point3 max_)
    : min(std::move(min_))
    , max(std::move(max_)) {}

  bool hit(ray const& r, float t_min, float t_max) const noexcept {
    vec3 const invD = vec3{1.f} / r.direction;
    vec3 const t0tmp = (min - r.origin) * invD;
    vec3 const t1tmp = (max - r.origin) * invD;
    vec3 const t0 = select(invD < vec3{0.f}, t1tmp, t0tmp);
    vec3 const t1 = select(invD < vec3{0.f}, t0tmp, t1tmp);
    vec3 const tmin = select(t0 > vec3(t_min), t0, vec3(t_min));
    vec3 const tmax = select(t1 < vec3(t_max), t1, vec3(t_max));
    mask32x4 const max_le_min = (tmax <= tmin);
    simd::float32x4 const vcmp =
      _mm_cmp_ps(_mm_castsi128_ps(max_le_min), _mm_set1_ps(0.f), _CMP_EQ_OQ);
    int const mask = _mm_movemask_ps(vcmp);
    return (mask != 0xff);
  }
}; // struct aabb

inline aabb surrounding_box(aabb const& box0, aabb const& box1) noexcept {
  return {min(box0.min, box1.min), max(box0.max, box1.max)};
}

} // namespace math

#endif // TR_MATH_AABB_H_
