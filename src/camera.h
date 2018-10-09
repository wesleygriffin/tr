#ifndef TR_CAMERA_H_
#define TR_CAMERA_H_

#include "math/scalar.h"
#include "math/random.h"
#include "math/ray.h"
#include "math/vec2.h"
#include <cmath>

template <class G>
inline math::vec3 random_in_unit_disk(G& gen) {
  std::uniform_real_distribution<float> dis(0.f, 1.f);
  math::vec3 p;
  do {
    p = math::vec3(dis(gen), dis(gen), 0.f) * 2.f - math::vec3(1.f, 1.f, 0.f);
  } while (math::square(p).x >= 1.0f);
  return p;
}

struct camera {
  float vfov_rad;
  float lens_radius;
  math::point3 origin;
  math::vec3 w, u, v;
  math::vec3 vertical;
  math::vec3 horizontal;
  math::point3 lower_left;
  std::uniform_real_distribution<float> dis{0.f, 1.f};

  camera(float vfov_deg, float aspect, float aperture, float focus_dist,
         math::point3 look_from = {0.f, 0.f, 0.f},
         math::point3 look_at = {0.f, 0.f, -1.f},
         math::vec3 view_up = {0.f, 1.f, 0.f})
    : vfov_rad(vfov_deg * float(M_PI) / 180.f)
    , lens_radius(aperture / 2.f)
    , origin(look_from)
    , w(math::normalize(look_from - look_at))
    , u(math::normalize(math::cross(view_up, w)))
    , v(math::cross(w, u)) {
    float const half_height = std::tan(vfov_rad / 2.f);
    float const half_width = aspect * half_height;
    vertical = v * focus_dist * half_height * 2.f;
    horizontal = u * focus_dist * half_width * 2.f;
    lower_left = origin - u * focus_dist * half_width -
                 v * focus_dist * half_height - w * focus_dist;
  }

  camera() noexcept = default;
  camera(camera const&) noexcept = default;
  camera(camera&&) noexcept = default;
  camera& operator=(camera const&) noexcept = default;
  camera& operator=(camera&&) noexcept = default;

  math::ray get_ray(math::pcg& gen, float s, float t,
                    math::vec2 const& time_interval = {0.f, 0.f}) noexcept {
    math::vec3 const rd = random_in_unit_disk(gen) * lens_radius;
    math::vec3 const offset = u * math::vec3(rd.x) + v * math::vec3(rd.y);
    float const time = math::lerp(time_interval.x, time_interval.y, dis(gen));
    return {origin + offset,
            (lower_left + horizontal * s + vertical * t) - origin - offset,
            time};
  }
}; // struct camera

#endif // TR_CAMERA_H_
