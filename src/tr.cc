#include "bvh.h"
#include "camera.h"
#include "fmt/format.h"
#include "hitable_list.h"
#include "material.h"
#include "math/color.h"
#include "math/random.h"
#include "math/ray.h"
#include "math/types.h"
#include "sphere.h"
#include "stb_image_write.h"
#include "tbb/tbb.h"
#include <atomic>
#include <cfloat>
#include <chrono>
#include <cstdio>
#include <memory>
#include <vector>

template <class G>
math::color4 color(G& gen, math::ray const& r, hitable const* world, int depth,
                   int& num_rays) {
  num_rays += 1;
  hit_record const rec = world->hit(r, 0.001f, FLT_MAX);
  if (rec.is_hit()) {
    math::color4 attenuation;
    math::ray scattered;
    if (depth < 50 && rec.mat->scatter(gen, r, rec, attenuation, scattered)) {
      return attenuation * color(gen, scattered, world, depth + 1, num_rays);
    } else {
      return math::color4(0.0f);
    }
  } else {
    math::vec3 const unit_direction = math::normalize(r.direction);
    return math::lerp(math::color4(1.0f), math::color4(0.5f, 0.5f, 1.0f, 1.0f),
                      0.5f * (unit_direction.y + 1.0f));
  }
}

template <class Sseq>
std::shared_ptr<hitable> generate_spheres(Sseq& seed) {
  math::pcg gen(seed);
  std::uniform_real_distribution<float> dis{0.f, 1.f};

  std::shared_ptr<hitable_list> scene = std::make_shared<hitable_list>();
  scene->push_back(std::make_shared<sphere>(
    math::point3{0.f, -1000.f, -1.f}, 1000.f,
    std::make_unique<lambertian>(std::make_unique<checker_texture>(
      std::make_unique<constant_texture>(
        math::color4{0.45f, 0.45f, 0.45f, 1.0f}),
      std::make_unique<constant_texture>(
        math::color4{0.9f, 0.9f, 0.9f, 1.f})))));

  for (int i = -11; i < 11; ++i) {
    for (int j = -11; j < 11; ++j) {
      float const choose_mat = dis(gen);
      math::point3 const center(i + 0.9f * dis(gen), 0.2f, j + 0.9f * dis(gen));
      if (math::length(center - math::point3(4.f, 0.2f, 0.f)).x > 0.9f) {
        if (choose_mat < 0.8f) {
          float const r = dis(gen) * dis(gen);
          float const g = dis(gen) * dis(gen);
          float const b = dis(gen) * dis(gen);
          scene->push_back(std::make_shared<sphere>(
            std::move(center), 0.2f,
            std::make_unique<lambertian>(
              std::make_unique<constant_texture>(math::color4{r, g, b, 1.f}))));
        } else if (choose_mat < 0.95f) {
          float const r = 0.5f * (1.f + dis(gen));
          float const g = 0.5f * (1.f + dis(gen));
          float const b = 0.5f * (1.f + dis(gen));
          scene->push_back(std::make_shared<sphere>(
            std::move(center), 0.2f,
            std::make_unique<metal>(math::color4{r, g, b, 1.f},
                                    0.5f * dis(gen))));
        } else {
          scene->push_back(std::make_shared<sphere>(
            std::move(center), 0.2f, std::make_unique<dielectric>(1.5f)));
        }
      }
    }
  }

  scene->push_back(std::make_shared<sphere>(
    math::point3(0.f, 1.f, 0.f), 1.f, std::make_unique<dielectric>(1.5f)));
  scene->push_back(std::make_shared<sphere>(
    math::point3(-4.f, 1.f, 0.f), 1.f,
    std::make_unique<lambertian>(std::make_unique<constant_texture>(
      math::color4(0.4f, 0.2f, 0.1f, 1.0f)))));
  scene->push_back(std::make_shared<sphere>(
    math::point3(4.f, 1.f, 0.f), 1.f,
    std::make_unique<metal>(math::color4(0.7f, 0.6f, 0.5f, 1.0f), 0.f)));

  std::shared_ptr<bvh_node> root = std::make_shared<bvh_node>(
    gen, scene->data(), scene->size(), math::vec2{0.f, 0.f});
  return std::dynamic_pointer_cast<hitable>(root);
}

int main() {
  stbi_flip_vertically_on_write(1);

  int nx = 1200;
  int ny = 800;
  int ns = 32;
  std::unique_ptr<uint8[]> pixels(new uint8[nx * ny * 3]);

  math::point3 look_from(13.f, 2.f, 3.f);
  math::point3 look_at(0.f, 0.f, 0.f);
  float const dist_to_focus = 10.f;
  float const aperture = 0.1f;
  camera cam(20.f, float(nx) / float(ny), aperture, dist_to_focus, look_from,
             look_at);

  math::random_device_seed rd;
  std::shared_ptr<hitable> world = generate_spheres(rd);

  std::atomic<uint64> total_rays{0};
  auto const start = std::chrono::system_clock::now();

  tbb::parallel_for(tbb::blocked_range3d<int, int, int>(0, ns, 0, ny, 0, nx),
                    [&](tbb::blocked_range3d<int, int, int> const& r) {
                      int const pages_begin = r.pages().begin();
                      int const pages_end = r.pages().end();
                      int const rows_begin = r.rows().begin();
                      int const rows_end = r.rows().end();
                      int const cols_begin = r.cols().begin();
                      int const cols_end = r.cols().end();

                      math::pcg gen(rd);
                      std::uniform_real_distribution<float> dis{0.f, 1.f};

                      uint8* p = pixels.get();
                      int num_rays = 0;

                      for (int j = rows_begin; j != rows_end; ++j) {
                        for (int i = cols_begin; i != cols_end; ++i) {
                          math::color4 col(0.f, 0.f, 0.f, 1.f);

                          for (int s = pages_begin; s != pages_end; ++s) {
                            float const u = float(i + dis(gen)) / float(nx);
                            float const v = float(j + dis(gen)) / float(ny);
                            math::ray const ray = cam.get_ray(gen, u, v);
                            col += color(gen, ray, world.get(), 0, num_rays);
                          }

                          col /= float(pages_end - pages_begin);
                          col = math::sqrt(col);
                          int const offset = j * nx * 3 + i * 3;

                          p[offset + 0] = uint8(255.99 * col.r);
                          p[offset + 1] = uint8(255.99 * col.g);
                          p[offset + 2] = uint8(255.99 * col.b);
                        }
                      }

                      total_rays += num_rays;
                    });

  auto const end = std::chrono::system_clock::now();
  float const mrays = total_rays / 1000.f / 1000.f / 1000.f;
  std::chrono::duration<float> dur_s = end - start;

  std::FILE* fh = std::fopen("tr.log", "w");
  fmt::print(fh, "rays: {} Mrays: {} s: {} Mrays/s: {}", total_rays, mrays,
             dur_s.count(), mrays / dur_s.count());
  std::fclose(fh);

  stbi_write_png("tr.png", nx, ny, 3, pixels.get(), nx * 3 * sizeof(uint8));
}
