#pragma once

#include <iostream>
#include <math.h>

#include "tools.hpp"

template <typename T = float>
class point {
private:
    T x = NAN;
    T y = NAN;
    T z = NAN;
public:
    point(T x, T y, T z) : x(x), y(y), z(z) {};

    void print() const {
        std::cout << x << " " << y << " " << z << std::endl;
    }

    bool valid() const {
        return !isnan(x) && !isnan(y) && !isnan (z);
    }

    T get_x() const {
        return x;
    }

    T get_y() const {
        return y;
    }

    T get_z() const {
        return z;
    }

    T& x_() {
        return x;
    }

    T& y_() {
        return y;
    }

    T& z_() {
        return z;
    }

    float length() const {
        return x*x + y*y + z*z;
    }

    point swap(point& other) {
        std::swap(x, other.x_());
        std::swap(y, other.y_());
        std::swap(z, other.z_());
        
        return *this;
    }

    point<T> normalize() {
        if (cmp(length(), 0)) {
            return *this;
        }

        return (*this) * (1 / sqrt(length()));
    }
};

template<typename T = float>
point<T> vec_multiply(const point<T>& lhs, const point<T>& rhs) {
    point<T> result(lhs.get_y() * rhs.get_z() - lhs.get_z() * rhs.get_y(),
                    lhs.get_z() * rhs.get_x() - lhs.get_x() * rhs.get_z(),
                    lhs.get_x() * rhs.get_y() - lhs.get_y() * rhs.get_x());

    return result;
}

template<typename T = float>
T scalar_multiply(const point<T>& lhs, const point<T>& rhs) {
    return lhs.get_x() * rhs.get_x() + lhs.get_y() * rhs.get_y() + lhs.get_z() * rhs.get_z();
}
template<typename T = float>
bool operator==(const point<T>& lhs, const point<T>& rhs) {
    if (cmp(lhs.get_x(), rhs.get_x()) && cmp(lhs.get_y(), rhs.get_y()) && cmp(lhs.get_z(), rhs.get_z()))
        return true;
    return false;
}

template<typename T = float>
bool operator!=(const point<T>& lhs, const point<T>& rhs) {
    return !operator==(lhs, rhs);
}

template<typename T = float>
point<T> operator+(const point<T>& lhs, const point<T>& rhs) {
    point<T> result(lhs.get_x() + rhs.get_x(),
                    lhs.get_y() + rhs.get_y(),
                    lhs.get_z() + rhs.get_z());
    return result;
}

template<typename T = float>
point<T> operator-(const point<T>& lhs, const point<T>& rhs) {
    point<T> result(lhs.get_x() - rhs.get_x(),
                    lhs.get_y() - rhs.get_y(),
                    lhs.get_z() - rhs.get_z());
    return result;
}

template<typename T = float>
point<T> operator*(const point<T>& lhs, const T& rhs) {
    point<T> result(lhs.get_x() * rhs,
                    lhs.get_y() * rhs,
                    lhs.get_z() * rhs);
    return result;
}

template<typename T = float>
point<T> operator*(const T& lhs, const point<T>& rhs) {
    return rhs * lhs;
}