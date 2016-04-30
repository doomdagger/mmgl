//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_POINTLIGHT_H
#define RAYTRACER_POINTLIGHT_H


#include "mmgl/light/light.h"

namespace mmgl {

/**
 * PointLight class for a pointlight used in the scene.
 * Derived from Light base class.
 */
class PointLight : public Light {
public:
    PointLight(float x = 0, float y = 0, float z = 0,
               float r = 0, float g = 0, float b = 0) : Light{r, g, b}, _orig{x, y, z} { }

    PointLight(const Point &point, const Vector &rgb) : Light{rgb}, _orig{point} { }


    inline const Point &orig() const {
        return _orig;
    }

    /**
     * Set the color of this pointlight.
     * @param color a Vector of RGB values.
     */
    PointLight &in(const Vector &color);

    /**
     * Set the color of this pointlight.
     * @param r/g/b RBG values.
     */
    PointLight &in(float r, float g, float b);

    /**
     * Set the position of this pointlight.
     * @param position A point specifying the position
     */
    PointLight &at(const Point &position);

    /**
     * Set the position of this pointlight.
     * @param x/y/z A point(x, y, z) specifying the position
     */
    PointLight &at(float x, float y, float z);

private:
    Point _orig;
};

}

#endif //RAYTRACER_POINTLIGHT_H
