//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H


#include <iostream>
#include <memory>
#include <sstream>

#include "mmgl/surface/surface.h"
#include "mmgl/util/point.h"

namespace mmgl {

class Sphere : public Surface {
public:
    Sphere(float x = 0, float y = 0, float z = 0, float r = 0, const Material &material = Material{});

    Sphere(const Point &origin, float radius, const Material &material = Material{});

    Sphere(const Sphere &sphere);

    virtual Sphere *clone() const {
        return {new Sphere(*this)};
    }

    inline const Point origin() const {
        return _origin;
    }

    inline float radius() const {
        return _radius;
    }

    Sphere &at(const Point &central);

    Sphere &at(float x, float y, float z);

    Sphere &radius(float radius);

    Sphere &made_of(const Material &material);

    bool intersect(Ray &, const Render &) const;

    std::string to_string() const;

private:
    void init() {
        float x_min, y_min, z_min, x_max, y_max, z_max;
        x_min = _origin._x - _radius;
        y_min = _origin._y - _radius;
        z_min = _origin._z - _radius;

        x_max = _origin._x + _radius;
        y_max = _origin._y + _radius;
        z_max = _origin._z + _radius;

        box(x_min, y_min, z_min, x_max, y_max, z_max);
    }

    Point _origin;
    float _radius;
};

}

#endif //RAYTRACER_SPHERE_H
