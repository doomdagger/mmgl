//
// Created by lihe on 4/22/16.
//

#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include "point.h"
#include "vector.h"

class Surface;

class Intersection {
public:
    Intersection() : _t(0.0f), _point(), _normal(), _id(nullptr) { }

    Intersection(float t, const Point &point, const Vector &normal, const Surface *const id) : _t(t), _point(point),
                                                                                               _normal(normal),
                                                                                               _id(id) { }

    inline float t() const {
        return _t;
    }

    inline const Point &point() const {
        return _point;
    }

    inline const Vector &normal() const {
        return _normal;
    }

    inline const Surface *id() const {
        return _id;
    }

private:
    float _t;
    Point _point;
    Vector _normal;
    const Surface * _id;
};

#endif //RAYTRACER_INTERSECTION_H
