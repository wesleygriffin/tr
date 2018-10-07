#ifndef TR_MATH_POINT_FORMAT_H_
#define TR_MATH_POINT_FORMAT_H_

#include "math/point.h"
#include "fmt/format.h"

template <typename Char>
struct fmt::formatter<math::point3, Char> {
  fmt::basic_memory_buffer<Char> point3_format;

  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin()) {
    auto it = fmt::internal::null_terminating_iterator<Char>(ctx);
    if (*it == ':') ++it;

    auto end = it;
    while (*end && *end != '}') ++end;
    point3_format.reserve(end - it + 1);

    using fmt::internal::pointer_from;
    point3_format.append(pointer_from(it), pointer_from(end));
    point3_format.push_back('\0');

    return pointer_from(end);
  }

  template <typename FormatContext>
  auto format(math::point3 const& p, FormatContext& ctx)
    -> decltype(ctx.out()) {
    return format_to(ctx.begin(), "({}, {}, {})", p.x, p.y, p.z);
    /*
    return format_to(ctx.begin(), "({:{}}, {:{}}, {:{}}, {:{}})", p.x,
      &point3_format[0], p.y, &point3_format[0], p.z, &point3_format[0]);
    */
  }
};

#endif // TR_MATH_POINT_FORMAT_H_
