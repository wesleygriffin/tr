#ifndef TR_MATH_RAY_FORMAT_H_
#define TR_MATH_RAY_FORMAT_H_

#include "math/ray.h"
#include "math/vec_format.h"

template <typename Char>
struct fmt::formatter<math::ray, Char> {
  fmt::basic_memory_buffer<Char> ray_format;

  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin()) {
    auto it = fmt::internal::null_terminating_iterator<Char>(ctx);
    if (*it == ':') ++it;

    auto end = it;
    while (*end && *end != '}') ++end;
    ray_format.reserve(end - it + 1);

    using fmt::internal::pointer_from;
    ray_format.append(pointer_from(it), pointer_from(end));
    ray_format.push_back('\0');

    return pointer_from(end);
  }

  template <typename FormatContext>
  auto format(math::ray const& r, FormatContext& ctx) -> decltype(ctx.out()) {
    return format_to(ctx.begin(), "({}, {})", r.origin, r.direction);
  }
};

#endif // TR_MATH_RAY_FORMAT_H_
