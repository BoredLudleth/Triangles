#pragma once

#include "line.hpp"

template <typename T = float>
class plane {
 private:
  using point_t = point<T>;

  T a = NAN;
  T b = NAN;
  T c = NAN;
  T d = NAN;

 public:
  plane(const point<T>& aa, const point<T>& bb, const point<T>& cc) {
    point_t vec1 = aa - bb;
    point_t vec2 = cc - bb;

    a = vec1.y * vec2.z - vec1.z * vec2.y;
    b = vec1.z * vec2.x - vec1.x * vec2.z;
    c = vec1.x * vec2.y - vec1.y * vec2.x;
    d = -(a * aa.x + b * aa.y + c * aa.z);
  }

  plane(T a, T b, T c, T d) : a(a), b(b), c(c), d(d){};

  T get_a() const { return a; }
  T get_b() const { return b; }
  T get_c() const { return c; }
  T get_d() const { return d; }

  T substitute(point_t point) const {
    return a * point.x + b * point.y + c * point.z + d;
  }

  void print() const {
    std::cout << a << " " << b << " " << c << " " << d << std::endl;
  }
};

template <typename T = float>
bool operator==(const plane<T>& lhs, const plane<T>& rhs) {
  float k = 0;
  if (cmp(rhs.get_a(), 0)) {
    if (!cmp(lhs.get_a(), 0)) {
      return false;
    }
  } else {
    k = lhs.get_a() / rhs.get_a();
  }

  if (cmp(rhs.get_b(), 0)) {
    if (!cmp(lhs.get_b(), 0)) {
      return false;
    }
  } else {
    if (k == 0) {
      k = lhs.get_b() / rhs.get_b();
    } else if (!cmp(k, lhs.get_b() / rhs.get_b())) {
      return false;
    }
  }

  if (cmp(rhs.get_c(), 0)) {
    if (!cmp(lhs.get_c(), 0)) {
      return false;
    }
  } else {
    if (k == 0) {
      k = lhs.get_c() / rhs.get_c();
    } else if (!cmp(k, lhs.get_c() / rhs.get_c())) {
      return false;
    }
  }

  if (cmp(rhs.get_d(), 0)) {
    if (!cmp(lhs.get_d(), 0)) {
      return false;
    }
  } else {
    if (k == 0) {
      k = lhs.get_d() / rhs.get_d();
    } else if (!cmp(k, lhs.get_d() / rhs.get_d())) {
      return false;
    }
  }

  return true;
}
