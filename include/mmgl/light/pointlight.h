//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


#include "mmgl/light/light.h"
#include "mmgl/util/point.h"

namespace mmgl {

class PointLight : public Light {
public:
    PointLight(float x = 0, float y = 0, float z = 0,
               float r = 0, float g = 0, float b = 0) : Light{r, g, b}, _orig{x, y, z} { }

    PointLight(const Point &point, const Vector &rgb) : Light{rgb}, _orig{point} { }

    PointLight(const PointLight &light) : Light(light.color()), _orig{light.orig()} { }


    inline const Point &orig() const {
        return _orig;
    }

    PointLight &in(const Vector &color);

    PointLight &in(float r, float g, float b);

    PointLight &at(const Point &position);

    PointLight &at(float x, float y, float z);

private:
    Point _orig;
};

}

#endif //RAYTRACER_POINTLIGHT_H
