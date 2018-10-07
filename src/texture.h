#ifndef TR_TEXTURE_H_
#define TR_TEXTURE_H_

#include "math/color4.h"
#include "math/point3.h"
#include "math/vec2.h"

struct texture {
  virtual math::color4 value(math::vec2 const& uv, math::point3 const& p) const
    noexcept = 0;
}; // struct texture

struct constant_texture : public texture {
  math::color4 color;

  constant_texture(math::color4 c)
    : color(std::move(c)) {}

  virtual math::color4 value(math::vec2 const&, math::point3 const&) const
    noexcept override {
    return color;
  }
}; // struct constant_texture

struct checker_texture : public texture {
  std::unique_ptr<texture> odd, even;

  checker_texture(std::unique_ptr<texture> o, std::unique_ptr<texture> e)
    : odd(std::move(o))
    , even(std::move(e)) {}

  virtual math::color4 value(math::vec2 const&, math::point3 const&) const
    noexcept override;
}; // struct checker_texture

math::color4 checker_texture::value(math::vec2 const& uv,
                                    math::point3 const& p) const noexcept {
  float const sines =
    std::sin(10.f * p.x) * std::sin(10.f * p.y) * std::sin(10.f * p.z);
  if (sines < 0.f) {
    return odd->value(uv, p);
  } else {
    return even->value(uv, p);
  }
} // checker_texture::value

#endif // TR_TEXTURE_H_
