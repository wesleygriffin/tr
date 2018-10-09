#ifndef TR_SIMD_SIMD_H_
#define TR_SIMD_SIMD_H_

#include <immintrin.h>

#if defined(_MSC_VER)
#define SIMDAPI_CALL __vectorcall
#else
#define SIMDAPI_CALL
#endif

namespace simd {

template <class ScalarType, int VectorSize, class VectorType>
struct hardware_vector {
  using T = ScalarType;
  using V = VectorType;

  enum {
    ScalarBits = sizeof(ScalarType) * 8,
    VectorBits = sizeof(VectorType) * 8,
  };

  VectorType data{};

  constexpr hardware_vector() noexcept = default;
  constexpr hardware_vector(VectorType v) noexcept
    : data(v) {}

  operator VectorType const() const { return data; }
}; // struct hardware_vector

template <int ScalarBits, int VectorSize, class MaskType>
struct hardware_mask {
  MaskType data;

  constexpr hardware_mask() noexcept = default;
  constexpr hardware_mask(MaskType m) noexcept
    : data(m) {}

  operator MaskType() const { return data; }
}; // struct hardware_mask

static_assert(sizeof(float) == 4);
using float32x4 = hardware_vector<float, 4, __m128>;
using mask32x4 = hardware_mask<32, 4, __m128i>;

using int32x4 = hardware_vector<int32, 4, __m128i>;

template <class V>
V SIMDAPI_CALL zero() noexcept;

template <class V, class T>
V SIMDAPI_CALL set1(T s) noexcept;

template <class V, class T>
V SIMDAPI_CALL set4(T x, T y, T z, T w) noexcept;

template <class V, class T>
V SIMDAPI_CALL uload(T const* p) noexcept;

} // namespace simd

#include "simd/sse2_float128.h"
#include "simd/sse2_int128.h"

#endif // TR_SIMD_SIMD_H_
