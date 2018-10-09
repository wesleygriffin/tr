#ifndef TR_HITABLE_H_
#define TR_HITABLE_H_

#include "math/aabb.h"
#include "math/ray.h"
#include "math/vec2.h"

struct material;

struct hit_record {
  float t{-1.f};
  math::point3 point{};
  math::vec3 normal{};
  material* mat{nullptr};

  bool is_hit() const noexcept { return !(t < 0); }
}; // struct hit_record

struct hitable {
  virtual hit_record hit(math::ray const& r, float t_min, float t_max) const
    noexcept = 0;

  virtual bool bounding_box(math::vec2 const& time_interval,
                            math::aabb& box) const noexcept = 0;

  virtual ~hitable() noexcept {}
}; // struct hitable

#endif // TR_HITABLE_H_
