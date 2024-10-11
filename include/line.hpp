#pragma once

#include "point.hpp"
#include "tools.hpp"

template <typename T = float>
class line {
private:
    using vector_t = point<T>;
    using point_t = point<T>;

    vector_t v;
    point_t p;

public:
    line(const vector_t& v, const point_t& p) : v(v), p(p) {};

    vector_t get_vec() const {
        return v;
    }

    point_t get_point() const {
        return p;
    }

    void print() const {
        std::cout << "vec:";
        v.print();
        std::cout << "point:";
        p.print();
    }

    point<T> intersection (const line<T>& rhs) const {
        point<T> vec2(rhs.get_vec());
        point<T> point2(rhs.get_point());

        float s = 0;

        if (!cmp(vec2.get_x() * v.get_y(), vec2.get_y() * v.get_x())) {
            s = ((p.get_x() - point2.get_x()) * v.get_y() + (point2.get_y() - p.get_y()) * v.get_x())/(vec2.get_x() * v.get_y() - vec2.get_y() * v.get_x());

            point<T> answer = point2 + vec2 * s;
            return answer;
        }

        if (!cmp(vec2.get_x() * v.get_z(), vec2.get_z() * v.get_x())) {
            s = ((p.get_x() - point2.get_x()) * v.get_z() + (point2.get_z() - p.get_z()) * v.get_x())/(vec2.get_x() * v.get_z() - vec2.get_z() * v.get_x());

            point<T> answer = point2 + vec2 * s;
            return answer;
        }

        if (!cmp(vec2.get_z() * v.get_y(), vec2.get_y() * v.get_z())) {
            s = ((p.get_z() - point2.get_z()) * v.get_y() + (point2.get_y() - p.get_y()) * v.get_z())/(vec2.get_z() * v.get_y() - vec2.get_y() * v.get_z());

            point<T> answer = point2 + vec2 * s;;
            return answer;
        }

        point<T> answer(NAN, NAN, NAN);
        return answer;
    }
};

template<typename T = float>
bool operator==(const line<T>& lhs, const line<T>& rhs) {
    point<T> vec1(lhs.get_vec());
    point<T> point1(lhs.get_point());

    point<T> vec2(rhs.get_vec());
    point<T> point2(rhs.get_point());

    point<T> vec3 = point1 - point2;

    float k = 0;

    if (cmp(vec2.get_x(), 0)) {
        if (!cmp(vec1.get_x(), 0)) {
            return false;
        }
    } else {
        k = vec1.get_x() / vec2.get_x();
    }

    if (cmp(vec2.get_y(), 0)) {
        if (!cmp(vec1.get_y(), 0)) {
            return false;
        }
    } else {
        if (k == 0) {
            k = vec1.get_y() / vec2.get_y();
        } else if (!cmp(k, vec1.get_y() / vec2.get_y())) {
            return false;
        }
    }

    if (cmp(vec2.get_z(), 0)) {
        if (!cmp(vec1.get_z(), 0)) {
            return false;
        }
    } else {
        if (k == 0) {
            k = vec1.get_z() / vec2.get_z();
        } else if (!cmp(k, vec1.get_z() / vec2.get_z())) {
            return false;
        }
    }

    k = 0;
    if (vec3 == point<T>(0,0,0)) {
        return true;
    }
    
    if (cmp(vec3.get_x(), 0)) {
        if (!cmp(vec1.get_x(), 0)) {
            return false;
        }
    } else {
        k = vec1.get_x() / vec3.get_x();
    }

    if (cmp(vec3.get_y(), 0)) {
        if (!cmp(vec1.get_y(), 0)) {
            return false;
        }
    } else {
        if (k == 0) {
            k = vec1.get_y() / vec3.get_y();
        } else if (!cmp(k, vec1.get_y() / vec3.get_y())) {
            return false;
        }
    }

    if (cmp(vec3.get_z(), 0)) {
        if (!cmp(vec1.get_z(), 0)) {
            return false;
        }
    } else {
        if (k == 0) {
            k = vec1.get_z() / vec3.get_z();
        } else if (!cmp(k, vec1.get_z() / vec3.get_z())) {
            return false;
        }
    }

    return true;
}
