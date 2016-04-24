//
// Created by lihe on 4/22/16.
//

#ifndef RAYTRACER_SURFACE_H
#define RAYTRACER_SURFACE_H

#include <string>
#include <iostream>

#include "material.h"
#include "ray.h"
#include "bbox.h"
#include "common.h"

class Surface {
public:
    virtual ~Surface() { }

    inline const Material &material() const {
        return _material;
    }

    inline void material(const Material &_material) {
        Surface::_material = _material;
    }

    inline void box(float x_min, float y_min, float z_min,
                    float x_max, float y_max, float z_max) {
        _box.box(x_min, y_min, z_min, x_max, y_max, z_max);
    }

    inline const BBox &box() const {
        return _box;
    }

    inline std::pair<bool, float> box_intersect(const Ray &ray, bool isNode = false) const {
        return _box.intersect(ray, isNode);
    }

    inline Vector box_normal(const Point &inter_p) const {
        return _box.normal(inter_p);
    }

    virtual bool intersect(Ray &, const Render &) const = 0;

    virtual std::string to_string() const = 0;

private:
    Material _material;
    BBox _box;
};

std::ostream &operator<<(std::ostream &os, const Surface &surface);


#endif //RAYTRACER_SURFACE_H
