#ifndef TR_MATH_VEC_FORMAT_H_
#define TR_MATH_VEC_FORMAT_H_

#include "math/vec.h"
#include "fmt/format.h"

template <typename Char>
struct fmt::formatter<math::vec3, Char> {
  fmt::basic_memory_buffer<Char> vec3_format;

  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin()) {
    auto it = fmt::internal::null_terminating_iterator<Char>(ctx);
    if (*it == ':') ++it;

    auto end = it;
    while (*end && *end != '}') ++end;
    vec3_format.reserve(end - it + 1);

    using fmt::internal::pointer_from;
    vec3_format.append(pointer_from(it), pointer_from(end));
    vec3_format.push_back('\0');

    return pointer_from(end);
  }

  template <typename FormatContext>
  auto format(math::vec3 const& v, FormatContext& ctx) -> decltype(ctx.out()) {
    return format_to(ctx.begin(), "({}, {}, {})", v.x, v.y, v.z);
    /*
    return format_to(ctx.begin(), "({:{}}, {:{}}, {:{}}, {:{}})", v.x,
      &vec3_format[0], v.y, &vec3_format[0], v.z, &vec3_format[0]);
    */
  }
};

template <typename Char>
struct fmt::formatter<math::vec4, Char> {
  fmt::basic_memory_buffer<Char> vec4_format;

  template <typename ParseContext>
  constexpr auto parse(ParseContext& ctx) -> decltype(ctx.begin()) {
    auto it = fmt::internal::null_terminating_iterator<Char>(ctx);
    if (*it == ':') ++it;

    auto end = it;
    while (*end && *end != '}') ++end;
    vec4_format.reserve(end - it + 1);

    using fmt::internal::pointer_from;
    vec4_format.append(pointer_from(it), pointer_from(end));
    vec4_format.push_back('\0');

    return pointer_from(end);
  }

  template <typename FormatContext>
  auto format(math::vec4 const& v, FormatContext& ctx) -> decltype(ctx.out()) {
    return format_to(ctx.begin(), "({}, {}, {}, {})", v.x, v.y, v.z, v.w);
    /*
    return format_to(ctx.begin(), "({:{}}, {:{}}, {:{}}, {:{}})", v.x,
      &vec4_format[0], v.y, &vec4_format[0], v.z, &vec4_format[0],
      v.w, &vec4_format[0]);
    */
  }
};

#endif // TR_MATH_VEC_FORMAT_H_
