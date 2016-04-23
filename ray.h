//
// Created by lihe on 4/22/16.
//

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "point.h"
#include "vector.h"
#include "intersection.h"

#include <iostream>
#include <vector>

#define EPS 0.00005f

class Ray {
public:
    friend class Triangle;

    friend class Sphere;

    friend class Plane;

    friend class BBox;

    Ray(float pos_x = 0, float pos_y = 0, float pos_z = 0,
        float dir_x = 0, float dir_y = 0, float dir_z = 0);

    Ray(const Point &point, const Vector &vector);


    inline const Point &origin() const {
        return _origin;
    }

    inline const Vector &dir() const {
        return _dir;
    }

    inline const Intersection &intersection() const {
        return _intersection;
    }

    inline bool has_intersect() const {
        return _has_intersect;
    }

    inline void intersection(Intersection &&intersection) {
        _has_intersect = true;
        Ray::_intersection = intersection;
    }

    bool updatable(float t) const;

    bool has_block(float max) const;

private:
    Point _origin;
    Vector _dir;
    bool _has_intersect;
    Intersection _intersection; // closest intersection
};

std::ostream &operator<<(std::ostream &os, const Ray &ray);

#endif //RAYTRACER_RAY_H
