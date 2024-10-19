#pragma once

#include "point.hpp"
#include "tools.hpp"

namespace triangle_space {
template <typename T = float>
class line {
 private:
  using vector_t = point<T>;
  using point_t = point<T>;

  vector_t v;
  point_t p;

 public:
  line(const vector_t& v, const point_t& p) : v(v), p(p){};

  vector_t get_vec() const { return v; }

  point_t get_point() const { return p; }

  void print() const {
    std::cout << "vec:";
    v.print();
    std::cout << "point:";
    p.print();
  }

  point<T> intersection(const line<T>& rhs) const {
    point<T> vec2(rhs.get_vec());
    point<T> point2(rhs.get_point());

    float s = 0;

    if (!cmp(vec2.x * v.y, vec2.y * v.x)) {
      s = ((p.x - point2.x) * v.y + (point2.y - p.y) * v.x) /
          (vec2.x * v.y - vec2.y * v.x);

      point<T> answer = point2 + vec2 * s;
      return answer;
    }

    if (!cmp(vec2.x * v.z, vec2.z * v.x)) {
      s = ((p.x - point2.x) * v.z + (point2.z - p.z) * v.x) /
          (vec2.x * v.z - vec2.z * v.x);

      point<T> answer = point2 + vec2 * s;
      return answer;
    }

    if (!cmp(vec2.z * v.y, vec2.y * v.z)) {
      s = ((p.z - point2.z) * v.y + (point2.y - p.y) * v.z) /
          (vec2.z * v.y - vec2.y * v.z);

      point<T> answer = point2 + vec2 * s;
      ;
      return answer;
    }

    point<T> answer(NAN, NAN, NAN);
    return answer;
  }
};

template <typename T = float>
bool operator==(const line<T>& lhs, const line<T>& rhs) {
  point<T> vec1(lhs.get_vec().normalize());
  point<T> point1(lhs.get_point());

  point<T> vec2(rhs.get_vec().normalize());
  point<T> point2(rhs.get_point());

  point<T> vec3 = (point1 - point2).normalize();

  if (vec3.length() == 0) {
    if (vec1 == vec2 || vec1 == (vec2 * -1.f)) {
      return true;
    }
  } else {
    if (vec1 == vec2 || vec1 == (vec2 * -1.f)) {
      if (vec1 == vec3 || vec1 == (vec3 * -1.f)) {
        return true;
      }
    }
  }

  return false;
}
}  // namespace geo_objects
