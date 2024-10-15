#pragma once

#include <algorithm>
#include <iostream>

#include "line.hpp"
#include "plane.hpp"
#include "point.hpp"

namespace triangle_space {
  using geo_objects_space::point;
  using geo_objects_space::line;
  using geo_objects_space::plane;
  
template <typename T = float>
class triangle {
 private:

  point<T> a;
  point<T> b;
  point<T> c;

  bool isPoint() const {
    if (a == b && b == c) return true;
    return false;
  }

  point<T> get_line_vec_from_trg() const {
    point<T> zero(0, 0, 0);
    if (valid()) {
      return point<T>(NAN, NAN, NAN);
    }

    if (a - b != zero) {
      return a - b;
    }

    if (c - b != zero) {
      return c - b;
    }

    if (a - c != zero) {
      return a - c;
    }

    return point<T>(NAN, NAN, NAN);
  }

  bool point_in_triangle(const point<T>& p) const {
    point<T> v0 = a - b;
    point<T> v1 = c - a;
    point<T> v2 = b - c;

    point<T> p_a = vec_multiply(v0, p - b).normalize();
    point<T> p_b = vec_multiply(v1, p - a).normalize();
    point<T> p_c = vec_multiply(v2, p - c).normalize();

    point<T> zero(0, 0, 0);

    if ((p_a == zero && p_b == zero) || (p_a == zero && p_c == zero) ||
        (p_b == zero && p_c == zero)) {
      return true;
    }

    if (p_a == zero) {
      if (p_b == p_c) return true;
      return false;
    }

    if (p_b == zero) {
      if (p_a == p_c) return true;
      return false;
    }

    if (p_c == zero) {
      if (p_a == p_b) return true;
      return false;
    }

    if (p_a == p_b && p_b == p_c) return true;
    return false;
  }

  bool triangle_intersection(const line<T>& l) const {
    point<T> orig = l.get_point();
    point<T> dir = l.get_vec();

    point<T> e1 = b - a;
    point<T> e2 = c - a;
    point<T> h = vec_multiply(dir, e2);
    T is_on_parallel_plane = scalar_multiply(e1, h);
    if (cmp(is_on_parallel_plane, 0)) {
      // case when triangle and line in one plane
      line<T> f(e1, a);
      line<T> s(e2, a);
      line<T> t(e2 - e1, b);

      point<T> p1 = l.intersection(f);
      point<T> p2 = l.intersection(s);
      point<T> p3 = l.intersection(t);

      if (point_in_triangle(orig) || point_in_triangle(orig + dir)) return true;

      if (p1.valid() && point_in_triangle(p1) &&
          is_point_on_segment(p1, orig, orig + dir))
        return true;

      if (p2.valid() && point_in_triangle(p2) &&
          is_point_on_segment(p2, orig, orig + dir))
        return true;

      if (p3.valid() && point_in_triangle(p3) &&
          is_point_on_segment(p3, orig, orig + dir))
        return true;

      return false;
    }

    T f = 1.0 / is_on_parallel_plane;
    point<T> s = orig - a;
    T u = f * scalar_multiply(s, h);

    if (u < 0.0 || u > 1.0) {
      return false;
    }

    point<T> q = vec_multiply(s, e1);
    T v = f * scalar_multiply(dir, q);

    if (v < 0.0 || u + v > 1.0) {
      return false;
    }

    T t = f * scalar_multiply(e2, q);

    if (t >= 0 && t <= 1) {
      return true;
    }
    return false;
  }

 public:
  size_t num = 0;

  triangle() = default;

  triangle(const point<T>& aa, const point<T>& bb, const point<T>& cc)
      : a{aa}, b{bb}, c{cc} {
    if (a.length() >= b.length()) {
      a.swap(b);
    }

    if (a.length() >= c.length()) {
      a.swap(c);
    }

    if (b.length() >= c.length()) {
      b.swap(c);
    }
  };

  // NOTE: in triangle length(a) <= length(b) <= length(c)
  triangle(const T& x1, const T& y1, const T& z1, const T& x2, const T& y2,
           const T& z2, const T& x3, const T& y3, const T& z3)
      : a(point<T>(x1, y1, z1)), b(point<T>(x2, y2, z2)), c(point<T>(x3, y3, z3)) {
    if (a.length() <= b.length()) {
      a.swap(b);
    }

    if (a.length() <= c.length()) {
      a.swap(c);
    }

    if (b.length() <= c.length()) {
      b.swap(c);
    }
  };

  void print() const {
    a.print();
    b.print();
    c.print();
  }

  bool valid() const {
    if (a.valid() && b.valid() && c.valid()) {
      point<T> vec1(a.x - b.x, a.y - b.y, a.z - b.z);
      point<T> vec2(c.x - b.x, c.y - b.y, c.z - b.z);

      if (cmp(fabs(scalar_multiply(vec1, vec2)),
              sqrt(vec1.length() * vec2.length()))) {
        return false;
      }

      if (a == b || b == c) {
        return false;
      }
      return true;
    }

    return false;
  }

  point<T> get_a() const { return a; }

  point<T> get_b() const { return b; }

  point<T> get_c() const { return c; }

  T min_x() const { return std::min(std::min(a.x, b.x), std::min(b.x, c.x)); }

  T max_x() const { return std::max(std::max(a.x, b.x), std::max(b.x, c.x)); }

  T min_y() const { return std::min(std::min(a.y, b.y), std::min(b.y, c.y)); }

  T max_y() const { return std::max(std::max(a.y, b.y), std::max(b.y, c.y)); }

  T min_z() const { return std::min(std::min(a.z, b.z), std::min(b.z, c.z)); }

  T max_z() const { return std::max(std::max(a.z, b.z), std::max(b.z, c.z)); }

  bool intersection(const triangle<T>& rhs) const {
    size_t num_of_valid = valid();
    num_of_valid += rhs.valid();
    switch (num_of_valid) {
      case 0: {
        // two points
        if (isPoint() && rhs.isPoint()) {
          return (a == rhs.get_a());
        }

        // two lines
        if (!isPoint() && !rhs.isPoint()) {
          line<T> first(get_line_vec_from_trg(), a);
          line<T> second(rhs.get_line_vec_from_trg(), rhs.get_a());

          point<T> inter = first.intersection(second);

          if ((is_point_on_segment(inter, a, b) ||
               is_point_on_segment(inter, a, c) ||
               is_point_on_segment(inter, b, c)) &&
              (is_point_on_segment(inter, a, b) ||
               is_point_on_segment(inter, rhs.get_a(), rhs.get_c()) ||
               is_point_on_segment(inter, rhs.get_b(), rhs.get_c()))) {
            return true;
          }

          if (first == second) {
            if (is_point_on_segment(a, rhs.get_a(), rhs.get_b()) ||
                is_point_on_segment(a, rhs.get_b(), rhs.get_c()) ||
                is_point_on_segment(a, rhs.get_a(), rhs.get_c())) {
              return true;
            }

            if (is_point_on_segment(b, rhs.get_a(), rhs.get_b()) ||
                is_point_on_segment(b, rhs.get_b(), rhs.get_c()) ||
                is_point_on_segment(b, rhs.get_a(), rhs.get_c())) {
              return true;
            }

            if (is_point_on_segment(c, rhs.get_a(), rhs.get_b()) ||
                is_point_on_segment(c, rhs.get_b(), rhs.get_c()) ||
                is_point_on_segment(c, rhs.get_a(), rhs.get_c())) {
              return true;
            }

            if (is_point_on_segment(rhs.get_a(), a, b) ||
                is_point_on_segment(rhs.get_a(), b, c) ||
                is_point_on_segment(rhs.get_a(), a, c)) {
              return true;
            }

            if (is_point_on_segment(rhs.get_b(), a, b) ||
                is_point_on_segment(rhs.get_b(), b, c) ||
                is_point_on_segment(rhs.get_b(), a, c)) {
              return true;
            }

            if (is_point_on_segment(rhs.get_c(), a, b) ||
                is_point_on_segment(rhs.get_c(), b, c) ||
                is_point_on_segment(rhs.get_c(), a, c)) {
              return true;
            }
          }
        }

        // one point, one line
        if (isPoint()) {
          if (is_point_on_segment(a, rhs.get_a(), rhs.get_c())) return true;
          return false;
        } else {
          if (is_point_on_segment(rhs.get_a(), a, c)) return true;
          return false;
        }
        break;
      }
      case 1: {
        // one point
        if (isPoint() || rhs.isPoint()) {
          if (isPoint()) {
            return rhs.point_in_triangle(get_a());
          } else {
            return point_in_triangle(rhs.get_a());
          }
        } else {
          // one line
          if (valid()) {
            line<T> l(rhs.get_c() - rhs.get_a(), rhs.get_a());
            return triangle_intersection(l);
          } else {
            line<T> l(c - a, a);

            return rhs.triangle_intersection(l);
          }
        }
        break;
      }
      case 2: {
        plane<T> lplane(a, b, c);
        plane<T> rplane(rhs.get_a(), rhs.get_b(), rhs.get_c());

        if (lplane.substitute(rhs.get_a()) > 0 &&
            lplane.substitute(rhs.get_b()) > 0 &&
            lplane.substitute(rhs.get_c()) > 0) {
          return false;
        }

        if (lplane.substitute(rhs.get_a()) < 0 &&
            lplane.substitute(rhs.get_b()) < 0 &&
            lplane.substitute(rhs.get_c()) < 0) {
          return false;
        }

        if (rplane.substitute(a) > 0 && rplane.substitute(b) > 0 &&
            rplane.substitute(c) > 0) {
          return false;
        }

        if (rplane.substitute(a) < 0 && rplane.substitute(b) < 0 &&
            rplane.substitute(c) < 0) {
          return false;
        }

        line<T> lfirst(b - a, a);
        line<T> lsecond(c - a, a);
        line<T> lthird(c - b, b);

        line<T> rfirst(rhs.get_b() - rhs.get_a(), rhs.get_a());
        line<T> rsecond(rhs.get_c() - rhs.get_a(), rhs.get_a());
        line<T> rthird(rhs.get_c() - rhs.get_b(), rhs.get_b());

        return rhs.triangle_intersection(lfirst) ||
               rhs.triangle_intersection(lsecond) ||
               rhs.triangle_intersection(lthird) ||
               triangle_intersection(rfirst) ||
               triangle_intersection(rsecond) || triangle_intersection(rthird);
        return false;
        break;
      }
      default:
        std::cout << "Unexpected error!" << std::endl;
    }

    return 0;
  }
};

template <typename T = float>
bool operator==(const triangle<T>& lhs, const triangle<T>& rhs) {
  if (lhs.get_a() == rhs.get_a() && lhs.get_b() == rhs.get_b() &&
      lhs.get_c() == rhs.get_c()) {
    return true;
  }

  return false;
}

template <typename T = float>
bool operator!=(const triangle<T>& lhs, const triangle<T>& rhs) {
  return !operator==(lhs, rhs);
}
}  // namespace triangle
