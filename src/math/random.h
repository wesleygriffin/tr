#ifndef TR_MATH_RANDOM_H_
#define TR_MATH_RANDOM_H_

// better random number generators: https://arvid.io/2018/07/02/better-cxx-prng
/* Copyright (c) 2018 Arvid Gerstmann. */
/* This code is licensed under MIT license. */

// Slight modifications made by Wesley Griffin to better mirror STL interface
// by using Sseq template constructor and seed method and also provide a
// random_device_seed class for seeding using std::random_device.

#include <cstdint>
#include <random>

namespace math {

class random_device_seed {
public:
  using result_type = uint32_t;

  random_device_seed() {}
  random_device_seed(random_device_seed const&) = delete;

  template <class RandomIt>
  void generate(RandomIt begin, RandomIt end) {
    for (RandomIt it = begin; it < end; ++it) *it = uint32_t(rd_());
  }

  std::size_t size() const noexcept { return 0; }

  template <class OutputIt>
  void param(OutputIt dest) const {}

private:
  std::random_device rd_;
}; // class random_device_seed

// truncated splitmix64: http://xoshiro.di.unimi.it/splitmix64.c
class splitmix {
public:
  using result_type = uint32_t;
  static constexpr result_type default_seed = 1u;

  static constexpr result_type min() { return 0; }
  static constexpr result_type max() { return UINT32_MAX; }

  friend bool operator==(splitmix const&, splitmix const&);
  friend bool operator!=(splitmix const&, splitmix const&);

  splitmix()
    : seed_(default_seed) {}

  template <class Sseq>
  explicit splitmix(Sseq& seq) {
    seed(seq);
  }

  template <class Sseq>
  void seed(Sseq& seq) {
    uint32_t s[2];
    seq.generate(s, s + 2);
    seed_ = uint64_t(s[0]) << 31 | uint64_t(s[1]);
  }

  result_type operator()() {
    uint64_t z = (seed_ += UINT64_C(0x9E3779B97F4A7C15));
    z = (z ^ (z >> 30)) * UINT64_C(0xBF58476D1CE4E5B9);
    z = (z ^ (z >> 27)) * UINT64_C(0x94D049BB133111EB);
    return result_type((z ^ (z >> 31)) >> 31);
  }

  void discard(unsigned long long n) {
    for (unsigned long long i = 0; i < n; ++i) operator()();
  }

private:
  uint64_t seed_;
}; // class splitmix

inline bool operator==(splitmix const& lhs, splitmix const& rhs) {
  return lhs.seed_ == rhs.seed_;
}

inline bool operator!=(splitmix const& lhs, splitmix const& rhs) {
  return lhs.seed_ != rhs.seed_;
}

// truncated xorshift32
class xorshift {
public:
  using result_type = uint32_t;

  static constexpr result_type min() { return 0; }
  static constexpr result_type max() { return UINT32_MAX; }

  friend bool operator==(xorshift const&, xorshift const&);
  friend bool operator!=(xorshift const&, xorshift const&);

  xorshift()
    : seed_(0xc1f651c67c62c6e0ull) {}

  template <class Sseq>
  explicit xorshift(Sseq& seq) {
    seed(seq);
  }

  template <class Sseq>
  void seed(Sseq& seq) {
    uint32_t s[2];
    seq.generate(s, s + 2);
    seed_ = uint64_t(s[0]) << 31 | uint64_t(s[1]);
  }

  result_type operator()() {
    uint64_t result = seed_ * 0xd989bcacc137dcd5ull;
    seed_ ^= seed_ >> 11;
    seed_ ^= seed_ << 31;
    seed_ ^= seed_ >> 18;
    return uint32_t(result >> 32ull);
  }

  void discard(unsigned long long n) {
    for (unsigned long long i = 0; i < n; ++i) operator()();
  }

private:
  uint64_t seed_;
}; // class xorshift

inline bool operator==(xorshift const& lhs, xorshift const& rhs) {
  return lhs.seed_ == rhs.seed_;
}

inline bool operator!=(xorshift const& lhs, xorshift const& rhs) {
  return lhs.seed_ != rhs.seed_;
}

// pcg32: http://www.pcg-random.org/download.html
class pcg {
public:
  using result_type = uint32_t;

  static constexpr result_type min() { return 0; }
  static constexpr result_type max() { return UINT32_MAX; }

  friend bool operator==(pcg const&, pcg const&);
  friend bool operator!=(pcg const&, pcg const&);

  pcg()
    : state_(0x853c49e6748fea9bull)
    , inc_(0xda3e39cb94b95bdbull) {}

  template <class Sseq>
  explicit pcg(Sseq& seq) {
    seed(seq);
  }

  template <class Sseq>
  void seed(Sseq& seq) {
    uint32_t s[2];

    seq.generate(s, s + 2);
    uint64_t const s0 = uint64_t(s[0]) << 31 | uint64_t(s[1]);

    seq.generate(s, s + 2);
    uint64_t const s1 = uint64_t(s[0]) << 31 | uint64_t(s[1]);

    state_ = 0;
    inc_ = (s1 << 1) | 1;
    (void)operator()();
    state_ += s0;
    (void)operator()();
  }

  result_type operator()() {
    uint64_t const oldstate = state_;
    state_ = oldstate * 6364136223846793005ull + inc_;
    uint32_t const xorshifted = uint32_t(((oldstate >> 18u) ^ oldstate) >> 27u);
    int rot = oldstate >> 59u;
    return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
  }

  void discard(unsigned long long n) {
    for (unsigned long long i = 0; i < n; ++i) operator()();
  }

private:
  uint64_t state_;
  uint64_t inc_;
}; // class pcg

inline bool operator==(pcg const& lhs, pcg const& rhs) {
  return lhs.state_ == rhs.state_ && lhs.inc_ == rhs.inc_;
}

inline bool operator!=(pcg const& lhs, pcg const& rhs) {
  return lhs.state_ != rhs.state_ || lhs.inc_ != rhs.inc_;
}

} // namespace math

#endif // TR_MATH_RANDOM_H_
