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
    plane (const point<T>& aa, const point<T>& bb, const point<T>& cc) {
        point_t vec1 = aa - bb;
        point_t vec2 = cc - bb;

        a = vec1.get_y() * vec2.get_z() - vec1.get_z() * vec2.get_y();
        b = vec1.get_z() * vec2.get_x() - vec1.get_x() * vec2.get_z();
        c = vec1.get_x() * vec2.get_y() - vec1.get_y() * vec2.get_x();
        d = -(a * aa.get_x() + b * aa.get_y() + c * aa.get_z());
    }

    plane (T a, T b, T c, T d) : a(a), b(b), c(c), d(d) {};

    T get_a() const {
        return a;
    }
    T get_b() const {
        return b;
    }
    T get_c() const {
        return c;
    }
    T get_d() const {
        return d;
    }

    T substitute(point_t point) const {
        return a * point.get_x() + b * point.get_y() + c * point.get_z() + d;
    }

    void print() const {
        std::cout << a << " " << b << " " << c << " " << d << std::endl;
    }
};

template<typename T = float>
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
