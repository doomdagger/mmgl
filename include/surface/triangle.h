//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H


#include <iostream>
#include <sstream>

#include "surface/surface.h"

class Triangle : public Surface {
public:
    Triangle(float x1 = 0, float y1 = 0, float z1 = 0,
             float x2 = 0, float y2 = 0, float z2 = 0,
             float x3 = 0, float y3 = 0, float z3 = 0);

    Triangle(const Point &p1, const Point &p2, const Point &p3);

    bool intersect(Ray &, const Render &) const;

    std::string to_string() const;

    Triangle &point_one(const Point &p1);

    Triangle &point_two(const Point &p2);

    Triangle &point_three(const Point &p3);

    Triangle &point_one(float x, float y, float z);

    Triangle &point_two(float x, float y, float z);

    Triangle &point_three(float x, float y, float z);

    Triangle &made_of(const Material &material);

private:
    void init() {
        Vector p12 = _p2 - _p1;
        Vector p13 = _p3 - _p1;
        _norm = p12.cross(p13);
        _norm.normalize();
        // init cache too
        _a = _p1._x - _p2._x;
        _b = _p1._y - _p2._y;
        _c = _p1._z - _p2._z;
        _d = _p1._x - _p3._x;
        _e = _p1._y - _p3._y;
        _f = _p1._z - _p3._z;

        float x_min, y_min, z_min, x_max, y_max, z_max;
        x_min = std::min(std::min(_p1._x, _p2._x), _p3._x);
        y_min = std::min(std::min(_p1._y, _p2._y), _p3._y);
        z_min = std::min(std::min(_p1._z, _p2._z), _p3._z);
        x_max = std::max(std::max(_p1._x, _p2._x), _p3._x);
        y_max = std::max(std::max(_p1._y, _p2._y), _p3._y);
        z_max = std::max(std::max(_p1._z, _p2._z), _p3._z);

        box(x_min, y_min, z_min, x_max, y_max, z_max);
    }

    Point _p1;
    Point _p2;
    Point _p3;
    // decide to cache triangle's unit normal vector, because it's always the same one
    Vector _norm;
    // cache a, b, c, d, e, f
    float _a, _b, _c, _d, _e, _f;
};


#endif //RAYTRACER_TRIANGLE_H
