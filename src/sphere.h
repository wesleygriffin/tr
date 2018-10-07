#ifndef TR_SPHERE_H_
#define TR_SPHERE_H_

#include "hitable.h"
#include "material.h"

struct sphere : public hitable {
  math::point3 center;
  float radius;
  std::unique_ptr<material> mat;

  sphere(math::point3 c, float r, std::unique_ptr<material> m)
    : center(c)
    , radius(r)
    , mat(std::move(m)) {}

  virtual hit_record hit(math::ray const& r, float t_min, float t_max) const
    noexcept override;

  virtual bool bounding_box(math::vec2 const&, math::aabb& box) const
    noexcept override;
}; // struct sphere

inline hit_record sphere::hit(math::ray const& r, float t_min,
                              float t_max) const noexcept {
  hit_record rec;

  math::vec3 const oc = r.origin - center;
  math::vec3 const a = math::dot(r.direction, r.direction);
  math::vec3 const b = math::dot(oc, r.direction);
  math::vec3 const c = math::dot(oc, oc) - radius * radius;
  math::vec3 const discriminant = b * b - a * c;

  if (discriminant.x > 0) {
    math::vec3 const t1 = (-b - math::sqrt(discriminant)) / a;
    if (t1.x < t_max && t1.x > t_min) {
      rec.t = t1.x;
    } else {
      math::vec3 const t2 = (-b + math::sqrt(discriminant)) / a;
      if (t2.x < t_max && t2.x > t_min) { rec.t = t2.x; }
    }

    if (rec.is_hit()) {
      rec.point = r.point_at(rec.t);
      rec.normal = (rec.point - center) / radius;
      rec.mat = mat.get();
    }
  }

  return rec;
} // sphere::hit

inline bool sphere::bounding_box(math::vec2 const&, math::aabb& box) const
  noexcept {
  box.min = center - math::vec3(radius);
  box.max = center + math::vec3(radius);
  return true;
} // sphere::bounding_box

#endif // TR_SPHERE_H_
