//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "mmgl/util/vector.h"

Vector::Vector(float x, float y, float z) : _x{x}, _y{y}, _z{z} { }

Vector Vector::cross(const Vector &vector) const {
    Vector new_vec;
    new_vec._x = _y * vector._z - _z * vector._y;
    new_vec._y = _z * vector._x - _x * vector._z;
    new_vec._z = _x * vector._y - _y * vector._x;
    return std::move(new_vec);
}

Vector &Vector::operator+=(const Vector &vector) {
    _x += vector._x;
    _y += vector._y;
    _z += vector._z;
    return *this;
}

Vector &Vector::operator-=(const Vector &vector) {
    _x -= vector._x;
    _y -= vector._y;
    _z -= vector._z;
    return *this;
}

Vector &Vector::operator*=(float scalar) {
    _x *= scalar;
    _y *= scalar;
    _z *= scalar;
    return *this;
}

Vector &Vector::operator/=(float scalar) {
    _x /= scalar;
    _y /= scalar;
    _z /= scalar;
    return *this;
}

Vector operator+(const Vector &lhs, const Vector &rhs) {
    Vector new_vec(lhs);
    new_vec += rhs;
    return std::move(new_vec);
}

Vector operator-(const Vector &lhs, const Vector &rhs) {
    Vector new_vec(lhs);
    new_vec -= rhs;
    return std::move(new_vec);
}

Vector operator*(const Vector &lhs, float scalar) {
    Vector new_vec(lhs);
    new_vec *= scalar;
    return std::move(new_vec);
}

Vector operator/(const Vector &lhs, float scalar) {
    Vector new_vec(lhs);
    new_vec /= scalar;
    return std::move(new_vec);
}

std::ostream &operator<<(std::ostream &os, const Vector &vector) {
    os << "Vector: " << vector.x() << " " << vector.y() << " " << vector.z() << std::flush;
    return os;
}

Point operator+(const Point &point, const Vector &vector) {
    Point p{point};
    p.x(p.x() + vector.x());
    p.y(p.y() + vector.y());
    p.z(p.z() + vector.z());

    return std::move(p);
}

Vector operator*(const Vector &lhs, const Vector &rhs) {
    Vector vector{lhs};
    vector.x(lhs.x() * rhs.x());
    vector.y(lhs.y() * rhs.y());
    vector.z(lhs.z() * rhs.z());
    return std::move(vector);
}

Vector bisector(const Vector &lhs, const Vector &rhs) {
    Vector vector{lhs};
    vector += rhs;
    vector.normalize();
    return std::move(vector);
}