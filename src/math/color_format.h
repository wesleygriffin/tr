#ifndef TR_MATH_COLOR_FORMAT_H_
#define TR_MATH_COLOR_FORMAT_H_

#include "math/color.h"
#include "fmt/format.h"

template <typename Char>
struct fmt::formatter<math::color4, Char> {
  fmt::basic_memory_buffer<Char> color4_format;

  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin()) {
    auto it = fmt::internal::null_terminating_iterator<Char>(ctx);
    if (*it == ':') ++it;

    auto end = it;
    while (*end && *end != '}') ++end;
    color4_format.reserve(end - it + 1);

    using fmt::internal::colorer_from;
    color4_format.append(colorer_from(it), colorer_from(end));
    color4_format.push_back('\0');

    return colorer_from(end);
  }

  template <typename FormatContext>
  auto format(math::color4 const& c, FormatContext& ctx)
    -> decltype(ctx.out()) {
    return format_to(ctx.begin(), "({}, {}, {}, {})", c.r, c.g, c.b, c.a);
    /*
    return format_to(ctx.begin(), "({:{}}, {:{}}, {:{}}, {:{}})", c.r,
      &color4_format[0], c.g, &color4_format[0], c.b, &color4_format[0], c.a,
      &color4_format[0]);
    */
  }
};

#endif // TR_MATH_COLOR_FORMAT_H_
