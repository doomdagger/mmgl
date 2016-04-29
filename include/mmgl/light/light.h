//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "mmgl/util/vector.h"

namespace mmgl {

/**
 * Light is the base class for all lights.
 */
class Light {
public:
    Light(float r = 0, float g = 0, float b = 0) : _color{r, g, b} { }

    Light(const Vector &rgb) : _color{rgb} { }

    /**
     * Virtual function that can be overrided in derived class.
     */
    virtual inline const Vector &color() const {
        return _color;
    }

    /**
     * Set the color for this light.
     * @param color a vector representing the color values.
     */
    void color(const Vector &color);

    /**
     * Set the color for this light.
     * @param r/g/b r/g/b values representing the color of the light
     */
    void color(float r, float g, float b);

    /**
     * Virtual destructor.
     */
    virtual ~Light() { };
private:
    Vector _color;
};

}

#endif //RAYTRACER_LIGHT_H
