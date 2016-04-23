//
// Created by lihe on 4/22/16.
//

#ifndef RAYTRACER_POINT_H
#define RAYTRACER_POINT_H

#include <iostream>

class Point {
public:
    friend class Triangle;

    friend class Sphere;

    friend class Plane;

    friend class BBox;

    inline float x() const {
        return _x;
    }

    inline float y() const {
        return _y;
    }

    inline float z() const {
        return _z;
    }

    inline void x(float x) {
        _x = x;
    }

    inline void y(float y) {
        _y = y;
    }

    inline void z(float z) {
        _z = z;
    }

    Point(float x = 0, float y = 0, float z = 0);

private:
    float _x, _y, _z;
};

std::ostream &operator<<(std::ostream &, const Point &);

#endif //RAYTRACER_POINT_H
