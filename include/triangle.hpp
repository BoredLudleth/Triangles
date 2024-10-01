#pragma once

#include <iostream>
#include <algorithm>

#include "point.hpp"
#include "line.hpp"
#include "plane.hpp"

template <typename T = float>
class triangle {
private:
    using point_t = point<T>;
    point_t a;
    point_t b;
    point_t c;
public:
    size_t num = 0;
    triangle() = default;
    triangle(const point_t& aa, const point_t& bb, const point_t& cc) : a{aa}, b{bb}, c{cc} {
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

    //NOTE: in triangle length(a) <= length(b) <= length(c)
    triangle(const T& x1, const T& y1, const T& z1,
             const T& x2, const T& y2, const T& z2,
             const T& x3, const T& y3, const T& z3) : a(point_t(x1, y1, z1))
                                                    , b(point_t(x2, y2, z2))
                                                    , c(point_t(x3, y3, z3)) {
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
            point_t vec1 (a.get_x() - b.get_x(), a.get_y() - b.get_y(), a.get_z() - b.get_z());
            point_t vec2 (c.get_x() - b.get_x(), c.get_y() - b.get_y(), c.get_z() - b.get_z());

            if (cmp(fabs(scalar_multiply(vec1, vec2)), sqrt(vec1.length() * vec2.length()))) {
                return false;
            }

            if (a == b || b == c) {
                return false;
            }
            return true;
        }

        return false;
    }

    point_t get_a() const {
        return a;
    }

    point_t get_b() const {
        return b;
    }

    point_t get_c() const {
        return c;
    }

    T min_x() const {
        return std::min(std::min(a.get_x(), b.get_x()),  std::min(b.get_x(), c.get_x()));
    }

    T max_x() const {
        return std::max(std::max(a.get_x(), b.get_x()),  std::max(b.get_x(), c.get_x()));
    }

    T min_y() const {
        return std::min(std::min(a.get_y(), b.get_y()),  std::min(b.get_y(), c.get_y()));
    }

    T max_y() const {
        return std::max(std::max(a.get_y(), b.get_y()),  std::max(b.get_y(), c.get_y()));
    }

    T min_z() const {
        return std::min(std::min(a.get_z(), b.get_z()),  std::min(b.get_z(), c.get_z()));
    }

    T max_z() const {
        return std::max(std::max(a.get_z(), b.get_z()),  std::max(b.get_z(), c.get_z()));
    }

    bool isPoint() const {
        if (a == b && b ==c)
            return true;
        return false;
    }
    
};

template<typename T = float>
bool operator==(const triangle<T>& lhs, const triangle<T>& rhs) {
    if (lhs.get_a() == rhs.get_a() && lhs.get_b() == rhs.get_b() && lhs.get_c() == rhs.get_c()) {
         return true;
    }

    return false;
}

template<typename T = float>
bool operator!=(const triangle<T>& lhs, const triangle<T>& rhs) {
    return !operator==(lhs, rhs);
}

template <typename T = float>
bool triangle_intersection(const line<T>& l, const triangle<T>& trg) {
    point<T> orig = l.get_point();
    point<T> dir = l.get_vec();

    point<T> v0 = trg.get_a();
    point<T> v1 = trg.get_b();
    point<T> v2 = trg.get_c();

    point<T> e1 = v1 - v0;
    point<T> e2 = v2 - v0;
    point<T> h = vec_multiply(dir, e2);
    T a = scalar_multiply(e1,h);
    if (cmp(a, 0)) {
        //случай когда линия и треугольник в одной плоскости
        line<T> f(e1, v0);
        line<T> s(e2, v0);
        line<T> t(v2 - v1, v1);

        point<T> p1 = intersection(l, f);
        point<T> p2 = intersection(l, s);
        point<T> p3 = intersection(l, t);

        if (p1.valid() && point_in_triangle(p1, trg) && is_point_on_segment(p1, orig, orig + dir))
            return true;
        
        if (p2.valid() && point_in_triangle(p2, trg) && is_point_on_segment(p2, orig, orig + dir))
            return true;

        if (p3.valid() && point_in_triangle(p3, trg) && is_point_on_segment(p3, orig, orig + dir))
            return true;

        return false;
    }

    T f = 1.0 / a;
    point<T> s = orig - v0;
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
        // inter = orig + dir * t;
        return true;
    }
    return false;
}

template<typename T = float>
point<T> get_line_vec_from_trg(const triangle<T>& trg) {
    point<T> zero(0,0,0);
    if (trg.valid()) {
        return point<T>(NAN, NAN, NAN);
    }

    if (trg.get_a() - trg.get_b() != zero) {
        return trg.get_a() - trg.get_b();
    }

    if (trg.get_c() - trg.get_b() != zero) {
        return trg.get_c() - trg.get_b();
    }

    if (trg.get_a() - trg.get_c() != zero) {
        return trg.get_a() - trg.get_c();
    }

    return point<T>(NAN, NAN, NAN);
}

template<typename T = float>
bool intersection (const triangle<T>& lhs, const triangle<T>& rhs) {
    size_t num_of_valid = lhs.valid();
    num_of_valid += rhs.valid();
    switch(num_of_valid) {
        case 0:
            {
                // two points
                if(lhs.isPoint() && rhs.isPoint()) {
                    return (lhs.get_a() == rhs.get_a());
                }

                //two lines
                if (!lhs.isPoint() && !rhs.isPoint()) {
                    line<T> first(get_line_vec_from_trg(lhs), lhs.get_a());
                    line<T> second(get_line_vec_from_trg(rhs), rhs.get_a());

                    point<T> inter = intersection(first, second);

                    if((is_point_on_segment(inter, lhs.get_a(), lhs.get_b()) || is_point_on_segment(inter, lhs.get_a(), lhs.get_c()) ||
                       is_point_on_segment(inter, lhs.get_b(), lhs.get_c())) && (is_point_on_segment(inter, lhs.get_a(), lhs.get_b())||
                       is_point_on_segment(inter, rhs.get_a(), rhs.get_c()) || is_point_on_segment(inter, rhs.get_b(), rhs.get_c()))) {
                        return true;
                    }

                    if (first == second){
                        if(is_point_on_segment(lhs.get_a(), rhs.get_a(), rhs.get_b()) || is_point_on_segment(lhs.get_a(), rhs.get_b(), rhs.get_c()) ||
                           is_point_on_segment(lhs.get_a(), rhs.get_a(), rhs.get_c())) {
                        return true;
                        }

                        if(is_point_on_segment(lhs.get_b(), rhs.get_a(), rhs.get_b()) || is_point_on_segment(lhs.get_b(), rhs.get_b(), rhs.get_c()) ||
                           is_point_on_segment(lhs.get_b(), rhs.get_a(), rhs.get_c())) {
                        return true;
                        }

                        if(is_point_on_segment(lhs.get_c(), rhs.get_a(), rhs.get_b()) || is_point_on_segment(lhs.get_c(), rhs.get_b(), rhs.get_c()) ||
                           is_point_on_segment(lhs.get_c(), rhs.get_a(), rhs.get_c())) {
                        return true;
                        }

                        if(is_point_on_segment(rhs.get_a(), lhs.get_a(), lhs.get_b()) || is_point_on_segment(rhs.get_a(), lhs.get_b(), lhs.get_c()) ||
                           is_point_on_segment(rhs.get_a(), lhs.get_a(), lhs.get_c())) {
                        return true;
                        }

                        if(is_point_on_segment(rhs.get_b(), lhs.get_a(), lhs.get_b()) || is_point_on_segment(rhs.get_b(), lhs.get_b(), lhs.get_c()) ||
                           is_point_on_segment(rhs.get_b(), lhs.get_a(), lhs.get_c())) {
                        return true;
                        }

                        if(is_point_on_segment(rhs.get_c(), lhs.get_a(), lhs.get_b()) || is_point_on_segment(rhs.get_c(), lhs.get_b(), lhs.get_c()) ||
                           is_point_on_segment(rhs.get_c(), lhs.get_a(), lhs.get_c())) {
                        return true;
                        }
                    }
                }

                //one point, one line
                if (lhs.isPoint()) {
                    if(is_point_on_segment(lhs.get_a(), rhs.get_a(), rhs.get_c()))
                        return true;
                    return false;
                } else {
                    if(is_point_on_segment(rhs.get_a(), lhs.get_a(), lhs.get_c()))
                        return true;
                    return false;
                }
                break;
            }
        case 1:
            {
                // one point
                if (lhs.isPoint() || rhs.isPoint()) {
                    if (lhs.isPoint()) {
                        return point_in_triangle(lhs.get_a(), rhs);
                    } else {
                        return point_in_triangle(rhs.get_a(), lhs);
                    }
                } else {
                    // one line
                    if (lhs.valid()) {
                        line<T> l(rhs.get_c() - rhs.get_a(), rhs.get_a());
                        return triangle_intersection(l, lhs);
                    } else {
                        line<T> l(lhs.get_c() - lhs.get_a(), lhs.get_a());

                        return triangle_intersection(l, rhs);
                    }
                }
                break;
            }
        case 2:
            {
                plane<T> lplane(lhs.get_a(), lhs.get_b(), lhs.get_c());
                plane<T> rplane(rhs.get_a(), rhs.get_b(), rhs.get_c());

                if (lplane.substitute(rhs.get_a()) > 0 && lplane.substitute(rhs.get_b()) > 0 && rplane.substitute(rhs.get_c()) > 0) {
                    return false;
                }

                if (lplane.substitute(rhs.get_a()) < 0 && lplane.substitute(rhs.get_b()) < 0 && lplane.substitute(rhs.get_c()) < 0) {
                    return false;
                }

                if (rplane.substitute(lhs.get_a()) > 0 && rplane.substitute(lhs.get_b()) > 0 && rplane.substitute(lhs.get_c()) > 0) {
                    return false;
                }

                if (rplane.substitute(lhs.get_a()) < 0 && rplane.substitute(lhs.get_b()) < 0 && rplane.substitute(lhs.get_c()) < 0) {
                    return false;
                }

                line<T> lfirst(lhs.get_b() - lhs.get_a(), lhs.get_a());
                line<T> lsecond(lhs.get_c() - lhs.get_a(), lhs.get_a());
                line<T> lthird(lhs.get_c() - lhs.get_b(), lhs.get_b());

                line<T> rfirst(rhs.get_b() - rhs.get_a(), rhs.get_a());
                line<T> rsecond(rhs.get_c() - rhs.get_a(), rhs.get_a());
                line<T> rthird(rhs.get_c() - rhs.get_b(), rhs.get_b());

                return triangle_intersection(lfirst, rhs) || triangle_intersection(lsecond, rhs) || triangle_intersection(lthird, rhs) ||
                       triangle_intersection(rfirst, lhs) || triangle_intersection(rsecond, lhs) || triangle_intersection(rthird, lhs);
                return false;
                break;
            }
        default:
            std::cout << "Unexpected error!" << std::endl;
    }

    return 0;
}

template <typename T = float>
bool is_point_on_segment(const point<T>& p, const point<T>& a, const point<T>& b) {
    if (!p.valid()) {
        return false;
    }
    if (cmp(sqrt((p - a).length()) + sqrt((p - b).length()), sqrt((a - b).length()))) {
        return true;
    }
    return false;
}

template<typename T = float>
bool point_in_triangle(const point<T>& p, const triangle<T>& trg) {
    point<T> v0 = trg.get_a() - trg.get_b();
    point<T> v1 = trg.get_c() - trg.get_a();
    point<T> v2 = trg.get_b() - trg.get_c();

    point<T> p_a = vec_multiply(v0, p - trg.get_b()).normalize();
    point<T> p_b = vec_multiply(v1, p - trg.get_a()).normalize();
    point<T> p_c = vec_multiply(v2, p - trg.get_c()).normalize();

    point<T> zero(0,0,0);

    if ((p_a == zero && p_b == zero) || (p_a == zero && p_c == zero) || (p_b == zero && p_c == zero)) {
        return true;
    }

    if (p_a == zero) {
        if (p_b == p_c)
            return true;
        return false;
    }

    if (p_b == zero) {
        if (p_a == p_c)
            return true;
        return false;
    }

    if (p_c == zero) {
        if (p_a == p_b)
            return true;
        return false; 
    }

    if (p_a == p_b && p_b == p_c)
        return true;
    return false;
}
