#ifndef TR_HITABLE_LIST_H_
#define TR_HITABLE_LIST_H_

#include "math/aabb.h"
#include "hitable.h"
#include <memory>
#include <vector>

struct hitable_list final : public hitable {
  hitable_list() noexcept = default;

  void push_back(std::shared_ptr<hitable> h) { list_.push_back(std::move(h)); }

  virtual hit_record hit(math::ray const& r, float t_min, float t_max) const
    noexcept override;

  virtual bool bounding_box(math::vec2 const&, math::aabb& box) const
    noexcept override;

  std::shared_ptr<hitable>* data() noexcept { return list_.data(); }
  std::size_t size() const noexcept { return list_.size(); }

private:
  std::vector<std::shared_ptr<hitable>> list_;
}; // struct hitable_list

hit_record hitable_list::hit(math::ray const& r, float t_min, float t_max) const
  noexcept {
  hit_record closest;
  closest.t = t_max;
  bool hit_anything = false;

  for (auto&& h : list_) {
    hit_record const tmp = h->hit(r, t_min, closest.t);
    if (tmp.is_hit()) {
      hit_anything = true;
      closest = tmp;
    }
  }

  if (!hit_anything) closest.t = -1.f;
  return closest;
} // hitable_list::hit

bool hitable_list::bounding_box(math::vec2 const& time_interval,
                                math::aabb& box) const noexcept {
  if (list_.empty()) return false;

  math::aabb tmp;
  if (!list_[0]->bounding_box(time_interval, tmp)) {
    return false;
  } else {
    box = tmp;
  }

  for (std::size_t i = 1; i < list_.size(); ++i) {
    if (!list_[i]->bounding_box(time_interval, tmp)) {
      return false;
    } else {
      box = surrounding_box(box, tmp);
    }
  }

  return true;
} // hitable_list::bounding_box

#endif // TR_HITABLE_LIST_H_
