#ifndef TR_MATERIAL_H_
#define TR_MATERIAL_H_

#include "math/color4.h"
#include "math/random.h"
#include "math/ray.h"
#include "math/vec3.h"
#include "hitable.h"
#include "texture.h"

template <class G>
math::vec3 random_in_unit_sphere(G& gen) {
  std::uniform_real_distribution<float> dis(0.f, 1.f);
  math::vec3 p;
  do {
    p = math::vec3(dis(gen), dis(gen), dis(gen)) * 2.f - math::vec3(1.f);
  } while (math::square(p).x >= 1.0f);
  return p;
}

struct material {
  virtual bool scatter(math::pcg& gen, math::ray const& r_in,
                       hit_record const& rec, math::color4& attenuation,
                       math::ray& scattered) const noexcept = 0;

  virtual ~material() noexcept {}
}; // struct material

struct lambertian final : public material {
  std::unique_ptr<texture> albedo;

  lambertian(std::unique_ptr<texture> a) noexcept
    : albedo(std::move(a)) {}

  virtual bool scatter(math::pcg& gen, math::ray const&, hit_record const& rec,
                       math::color4& attenuation, math::ray& scattered) const
    noexcept override {
    math::point3 const target =
      rec.point + rec.normal + random_in_unit_sphere(gen);
    scattered = math::ray(rec.point, target - rec.point);
    attenuation = albedo->value({0.f, 0.f}, rec.point);
    return true;
  }
}; // struct lambertian

static inline math::vec3 MATHAPI_CALL reflect(math::vec3 v,
                                              math::vec3 n) noexcept {
  return v - math::dot(v, n) * 2.0f * n;
}

struct metal final : public material {
  math::color4 albedo;
  float fuzz;

  metal(math::color4 a, float f) noexcept
    : albedo(std::move(a)), fuzz(f) {}

  virtual bool scatter(math::pcg& gen, math::ray const& r_in,
                       hit_record const& rec, math::color4& attenuation,
                       math::ray& scattered) const noexcept override {
    math::vec3 const reflected = reflect(normalize(r_in.direction), rec.normal);
    scattered =
      math::ray(rec.point, reflected + random_in_unit_sphere(gen) * fuzz);
    attenuation = albedo;
    return (math::dot(scattered.direction, rec.normal).x > 0.f);
  }
}; // struct metal

inline bool refract(math::vec3 v, math::vec3 n, float ni_over_nt,
                    math::vec3& refracted) {
  math::vec3 const uv = math::normalize(v);
  float const dt = math::dot(uv, n).x;
  float const discriminant = 1.f - ni_over_nt * ni_over_nt * (1.f - dt * dt);

  if (discriminant > 0.f) {
    refracted = (uv - n * dt) * ni_over_nt - n * std::sqrt(discriminant);
    return true;
  } else {
    return false;
  }
} // refract

inline float schlick(float cosine, float ref_idx) noexcept {
  float r0 = (1.f - ref_idx) / (1.f + ref_idx);
  r0 = r0 * r0;
  return r0 + (1.f - r0) * std::pow((1.f - cosine), 5.f);
} // schlick

struct dielectric final : public material {
  float ref_idx;

  dielectric(float ri) noexcept : ref_idx(ri) {}

  virtual bool scatter(math::pcg& gen, math::ray const& r_in,
                       hit_record const& rec, math::color4& attenuation,
                       math::ray& scattered) const noexcept override {
    attenuation = math::color4(1.f, 1.f, 1.f, 1.f);
    scattered.origin = rec.point;

    std::uniform_real_distribution<float> dis(0.f, 1.f);
    float const DdotN = math::dot(r_in.direction, rec.normal).x;
    float const Dlen = math::length(r_in.direction).x;

    math::vec3 outward_normal;
    float ni_over_nt;
    float cosine;

    if (DdotN > 0.f) {
      outward_normal = -rec.normal;
      ni_over_nt = ref_idx;
      cosine = ref_idx * DdotN / Dlen;
    } else {
      outward_normal = rec.normal;
      ni_over_nt = 1.f / ref_idx;
      cosine = -DdotN / Dlen;
    }

    math::vec3 refracted;
    float reflect_prob;

    if (refract(r_in.direction, outward_normal, ni_over_nt, refracted)) {
      reflect_prob = schlick(cosine, ref_idx);
    } else {
      reflect_prob = 1.f;
    }

    if (dis(gen) < reflect_prob) {
      scattered.direction = reflect(r_in.direction, rec.normal);
    } else {
      scattered.direction = refracted;
    }

    return true;
  }
}; // struct dielectric

#endif // TR_MATERIAL_H_
