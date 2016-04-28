//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_INTERSECTION_H
#define RAYTRACER_INTERSECTION_H

#include <memory>
#include <cstdint>

#include "mmgl/util/point.h"
#include "mmgl/util/vector.h"

namespace mmgl {

class Surface;

class Intersection {
public:
    Intersection() : _t(0.0f), _point(), _normal(), _id(reinterpret_cast<uintptr_t>(nullptr)) { }

    Intersection(float t, const Point &point, const Vector &normal, const uintptr_t id) : _t(t), _point(point),
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

    inline uintptr_t id() const {
        return _id;
    }

private:
    float _t;
    Point _point;
    Vector _normal;
    uintptr_t _id;
};

}

#endif //RAYTRACER_INTERSECTION_H
