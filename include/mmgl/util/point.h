//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_POINT_H
#define RAYTRACER_POINT_H

#include <iostream>

namespace mmgl {

/**
 * Point class abstracts three dimensional points
 * Public member functions have obvious meanings as their names indicate.
 */
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

}

#endif //RAYTRACER_POINT_H
