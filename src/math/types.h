#ifndef TR_MATH_TYPES_H_
#define TR_MATH_TYPES_H_

#include <cstddef>
#include <cstdint>

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using float32 = float;
using float64 = double;

static_assert(sizeof(uint8) * 8 == 8);
static_assert(sizeof(uint16) * 8 == 16);
static_assert(sizeof(uint32) * 8 == 32);
static_assert(sizeof(uint64) * 8 == 64);

static_assert(sizeof(int8) * 8 == 8);
static_assert(sizeof(int16) * 8 == 16);
static_assert(sizeof(int32) * 8 == 32);
static_assert(sizeof(int64) * 8 == 64);

static_assert(sizeof(float32) * 8 == 32);
static_assert(sizeof(float64) * 8 == 64);

#if defined(_MSC_VER)
#define MATHAPI_CALL __vectorcall
#else
#define MATHAPI_CALL
#endif

#endif // TR_MATH_TYPES_H_
