#ifndef TR_BVH_H_
#define TR_BVH_H_

#include "hitable.h"
#include "math/random.h"
#include <algorithm>
#include <memory>
#include <stdexcept>

struct bvh_node : public hitable {
  std::uniform_int_distribution<int> dis{1, 3};
  std::shared_ptr<hitable> left{};
  std::shared_ptr<hitable> right{};
  math::aabb box{};

  constexpr bvh_node() noexcept = default;

  template <class G>
  bvh_node(G& gen, std::shared_ptr<hitable>* l, std::size_t n,
           math::vec2 const& time_interval);

  virtual hit_record hit(math::ray const& r, float t_min, float t_max) const
    noexcept override;

  virtual bool bounding_box(math::vec2 const&, math::aabb& b) const
    noexcept override;

  struct box_x_compare {
    bool operator()(std::shared_ptr<hitable> a, std::shared_ptr<hitable> b) {
      math::aabb abox, bbox;
      if (!a->bounding_box({0.f, 0.f}, abox) ||
          !b->bounding_box({0.f, 0.f}, bbox)) {
        throw std::runtime_error("box_x_compare: no bounding box");
      }
      return (abox.min.x - bbox.min.x < 0.f);
    }
  };

  struct box_y_compare {
    bool operator()(std::shared_ptr<hitable> a, std::shared_ptr<hitable> b) {
      math::aabb abox, bbox;
      if (!a->bounding_box({0.f, 0.f}, abox) ||
          !b->bounding_box({0.f, 0.f}, bbox)) {
        throw std::runtime_error("box_y_compare: no bounding box");
      }
      return (abox.min.y - bbox.min.y < 0.f);
    }
  };

  struct box_z_compare {
    bool operator()(std::shared_ptr<hitable> a, std::shared_ptr<hitable> b) {
      math::aabb abox, bbox;
      if (!a->bounding_box({0.f, 0.f}, abox) ||
          !b->bounding_box({0.f, 0.f}, bbox)) {
        throw std::runtime_error("box_z_compare: no bounding box");
      }
      return (abox.min.z - bbox.min.z < 0.f);
    }
  };
}; // struct bvh_node

template <class G>
inline bvh_node::bvh_node(G& gen, std::shared_ptr<hitable>* l, std::size_t n,
                          math::vec2 const& time_interval) {
  switch (dis(gen)) {
  case 0: std::sort(l, l + n, box_x_compare()); break;
  case 1: std::sort(l, l + n, box_y_compare()); break;
  case 2: std::sort(l, l + n, box_z_compare()); break;
  }

  if (n == 1) {
    left = right = l[0];
  } else if (n == 2) {
    left = l[0];
    right = l[1];
  } else {
    left = std::make_shared<bvh_node>(gen, l, n / 2, time_interval);
    right =
      std::make_shared<bvh_node>(gen, l + n / 2, n - n / 2, time_interval);
  }

  math::aabb box_left, box_right;
  if (!left->bounding_box({0.f, 0.f}, box_left) ||
      !right->bounding_box({0.f, 0.f}, box_right)) {
    throw std::runtime_error("bvh_node: no bounding box");
  }
  box = surrounding_box(box_left, box_right);
} // bvh_node::bvh_node

hit_record bvh_node::hit(math::ray const& r, float t_min, float t_max) const
    noexcept {
  if (!box.hit(r, t_min, t_max)) return {};

  hit_record const left_rec = left->hit(r, t_min, t_max);
  hit_record const right_rec = right->hit(r, t_min, t_max);

  if (left_rec.is_hit() && right_rec.is_hit()) {
    if (left_rec.t < right_rec.t) {
      return left_rec;
    } else {
      return right_rec;
    }
  } else if (left_rec.is_hit()) {
    return left_rec;
  } else if (right_rec.is_hit()) {
    return right_rec;
  } else {
    return {};
  }
} // bvh_node::hit

bool bvh_node::bounding_box(math::vec2 const&, math::aabb& b) const noexcept {
  b = box;
  return true;
}

#endif // TR_BVH_H_
