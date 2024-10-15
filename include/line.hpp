#pragma once

#include "point.hpp"
#include "tools.hpp"

namespace geo_objects_space {
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
  point<T> vec1(lhs.get_vec());
  point<T> point1(lhs.get_point());

  point<T> vec2(rhs.get_vec());
  point<T> point2(rhs.get_point());

  point<T> vec3 = point1 - point2;

  float k = 0;

  if (cmp(vec2.x, 0)) {
    if (!cmp(vec1.x, 0)) {
      return false;
    }
  } else {
    k = vec1.x / vec2.x;
  }

  if (cmp(vec2.y, 0)) {
    if (!cmp(vec1.y, 0)) {
      return false;
    }
  } else {
    if (k == 0) {
      k = vec1.y / vec2.y;
    } else if (!cmp(k, vec1.y / vec2.y)) {
      return false;
    }
  }

  if (cmp(vec2.z, 0)) {
    if (!cmp(vec1.z, 0)) {
      return false;
    }
  } else {
    if (k == 0) {
      k = vec1.z / vec2.z;
    } else if (!cmp(k, vec1.z / vec2.z)) {
      return false;
    }
  }

  k = 0;
  if (vec3 == point<T>(0, 0, 0)) {
    return true;
  }

  if (cmp(vec3.x, 0)) {
    if (!cmp(vec1.x, 0)) {
      return false;
    }
  } else {
    k = vec1.x / vec3.x;
  }

  if (cmp(vec3.y, 0)) {
    if (!cmp(vec1.y, 0)) {
      return false;
    }
  } else {
    if (k == 0) {
      k = vec1.y / vec3.y;
    } else if (!cmp(k, vec1.y / vec3.y)) {
      return false;
    }
  }

  if (cmp(vec3.z, 0)) {
    if (!cmp(vec1.z, 0)) {
      return false;
    }
  } else {
    if (k == 0) {
      k = vec1.z / vec3.z;
    } else if (!cmp(k, vec1.z / vec3.z)) {
      return false;
    }
  }

  return true;
}
}  // namespace geo_objects
