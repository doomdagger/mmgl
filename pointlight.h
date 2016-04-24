//
// Created by lihe on 4/23/16.
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


#include "light.h"
#include "point.h"

class PointLight : public Light {
public:
    PointLight(float x = 0, float y = 0, float z = 0,
               float r = 0, float g = 0, float b = 0) : Light{r, g, b}, _orig{x, y, z} { }

    PointLight(const Point &point, float r = 0, float g = 0, float b = 0) : Light{r, g, b}, _orig{point} { }


    inline const Point &orig() const {
        return _orig;
    }

    inline void orig(const Point &orig) {
        PointLight::_orig = orig;
    }

private:
    Point _orig;
};


#endif //RAYTRACER_POINTLIGHT_H