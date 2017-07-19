#pragma once

namespace fbvg {

template<typename T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
  if (v > hi) return hi;
  if (v < lo) return lo;
  return v;
}

template<typename T, typename Compare>
constexpr const T& clamp(const T& v, const T& lo, const T& hi, Compare comp) {
  if (comp(hi, v)) return hi;
  if (comp(v, lo)) return lo;
  return v;
}

}
