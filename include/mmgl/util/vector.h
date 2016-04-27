//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_VECTOR_H
#define RAYTRACER_VECTOR_H

#include <iostream>
#include <cmath>

#include "mmgl/util/point.h"

namespace mmgl {

class Vector {
public:
    friend class Triangle;

    friend class Sphere;

    friend class Plane;

    friend class BBox;

    Vector(float x = 0, float y = 0, float z = 0);

    inline float dot(const Vector &vector) const {
        return _x * vector._x + _y * vector._y + _z * vector._z;
    }

    Vector cross(const Vector &) const;

    inline void normalize() {
        *this /= magnitude();
    }

    inline float magnitude() const {
        return sqrtf(_x * _x + _y * _y + _z * _z);
    }

    Vector &operator+=(const Vector &);

    Vector &operator-=(const Vector &);

    Vector &operator*=(float scalar);

    Vector &operator/=(float scalar);

    inline float x() const {
        return _x;
    }

    inline float y() const {
        return _y;
    }

    inline float z() const {
        return _z;
    }

    inline void x(float _x) {
        Vector::_x = _x;
    }

    inline void y(float _y) {
        Vector::_y = _y;
    }

    inline void z(float _z) {
        Vector::_z = _z;
    }

private:
    float _x, _y, _z;
};

Vector operator+(const Vector &lhs, const Vector &rhs);

Vector operator-(const Vector &lhs, const Vector &rhs);

Vector operator*(const Vector &lhs, float scalar);

Vector operator*(const Vector &lhs, const Vector &rhs);

Vector operator/(const Vector &lhs, float scalar);

inline Vector operator-(const Point &lhs, const Point &rhs) {
    return std::move(Vector(lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z()));
}

Point operator+(const Point &point, const Vector &vector);

std::ostream &operator<<(std::ostream &os, const Vector &vector);

Vector bisector(const Vector &lhs, const Vector &rhs);

}

#endif //RAYTRACER_VECTOR_H
