#ifndef TR_MATH_COLOR_DETAIL_H_
#define TR_MATH_COLOR_DETAIL_H_

namespace math::detail {

template <class T, class V, int I>
struct scalar_accessor {
  V m{};

  scalar_accessor() noexcept = default;

  constexpr operator T() const noexcept { return simd::get_component<I>(m); }

  constexpr scalar_accessor& operator=(T s) noexcept {
    m = simd::set_component<I>(m, s);
    return *this;
  }

  constexpr scalar_accessor& operator+=(T s) noexcept {
    *this = T(*this) + s;
    return *this;
  }

  constexpr scalar_accessor& operator-=(T s) noexcept {
    *this = T(*this) - s;
    return *this;
  }

  constexpr scalar_accessor& operator*=(T s) noexcept {
    *this = T(*this) * s;
    return *this;
  }

  constexpr scalar_accessor& operator/=(T s) noexcept {
    *this = T(*this) / s;
    return *this;
  }
}; // struct scalar_accessor

} // namespace math::detail

#endif // TR_MATH_COLOR_DETAIL_H_
