#pragma once

#include <math.h>

#include <iostream>

#include "tools.hpp"

namespace geo_objects_space {

using triangle_space::cmp;

template <typename T = float>
class point {
 public:
  T x = NAN;
  T y = NAN;
  T z = NAN;
  point(T x, T y, T z) : x(x), y(y), z(z){};

  void print() const { std::cout << x << " " << y << " " << z << std::endl; }

  bool valid() const { return !isnan(x) && !isnan(y) && !isnan(z); }

  float length() const { return x * x + y * y + z * z; }

  point<T> normalize() {
    if (cmp(length(), 0)) {
      return *this;
    }

    return (*this) * (1 / sqrt(length()));
  }
};

template <typename T = float>
point<T> vec_multiply(const point<T>& lhs, const point<T>& rhs) {
  point<T> result(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z,
                  lhs.x * rhs.y - lhs.y * rhs.x);

  return result;
}

template <typename T = float>
T scalar_multiply(const point<T>& lhs, const point<T>& rhs) {
  return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}
template <typename T = float>
bool operator==(const point<T>& lhs, const point<T>& rhs) {
  if (cmp(lhs.x, rhs.x) && cmp(lhs.y, rhs.y) && cmp(lhs.z, rhs.z)) return true;
  return false;
}

template <typename T = float>
bool operator!=(const point<T>& lhs, const point<T>& rhs) {
  return !operator==(lhs, rhs);
}

template <typename T = float>
point<T> operator+(const point<T>& lhs, const point<T>& rhs) {
  point<T> result(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
  return result;
}

template <typename T = float>
point<T> operator-(const point<T>& lhs, const point<T>& rhs) {
  point<T> result(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
  return result;
}

template <typename T = float>
point<T> operator*(const point<T>& lhs, const T& rhs) {
  point<T> result(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
  return result;
}

template <typename T = float>
point<T> operator*(const T& lhs, const point<T>& rhs) {
  return rhs * lhs;
}

template <typename T = float>
bool is_point_on_segment(const point<T>& p, const point<T>& a,
                         const point<T>& b) {
  if (!p.valid()) {
    return false;
  }
  if (cmp(sqrt((p - a).length()) + sqrt((p - b).length()),
          sqrt((a - b).length()))) {
    return true;
  }
  return false;
}
}  // namespace geo_objects_space
