#ifndef TR_PERLIN_H_
#define TR_PERLIN_H_

#include "math/point3.h"
#include "math/vec3i.h"
#include "math/random.h"
#include <utility>
#include <memory>

struct perlin {
  template <class G>
  float noise(G& gen, math::point3 p) const noexcept;

  static std::unique_ptr<float[]> ranfloat;
  static std::unique_ptr<int[]> perm_x;
  static std::unique_ptr<int[]> perm_y;
  static std::unique_ptr<int[]> perm_z;

  template <class G>
  static void generate(G& gen);
}; // struct perlin

template <class G>
inline float perlin::noise(G& gen, math::point3 p) const noexcept {
  //if (!ranfloat) generate(gen, p);

  //math::vec3 const uvw = p - math::floor(p);
  //math::vec3i const ijk = (p * 4.f) & math::vec3(255);
  //return ranfloat[perm_x[ijk.x] ^ perm_y[ijk.y] ^ perm_z[ijk.z]];
  return -1.f;
} // perlin::noise

template <class G>
inline void perlin::generate(G& gen) {
#if 0
  std::uniform_real_distribution<float> dis{0.f, 1.f};

  ranfloat = new float[256];
  for (int i = 0; i < 256; ++i) ranfloat[i] = dis(gen);

  auto permute = [](int* p, int n) {
    for (int i = n - 1; i > 0; --i) {
      int target = int(dis(gen) * (i + 1));
      std::swap(p[i], p[target]);
    }
  };

  perm_x = new int[256];
  for (int i = 0; i < 256; ++i) p[i] = i;
  permute(perm_x.get(), 256);

  perm_y = new int[256];
  for (int i = 0; i < 256; ++i) p[i] = i;
  permute(perm_y.get(), 256);

  perm_z = new int[256];
  for (int i = 0; i < 256; ++i) p[i] = i;
  permute(perm_z.get(), 256);
#endif
}

#endif // TR_PERLIN_H_
