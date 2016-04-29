//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H


#include "mmgl/light/light.h"

namespace mmgl {

/**
 * Class for ambient light used in the scene.
 * Derived from the Light base class.
 */
class AmbientLight : public Light {
public:
    AmbientLight(float r, float g, float b) : Light{r, g, b} { }

    AmbientLight(const Vector &rgb) : Light{rgb} { }

    /**
     * Set the color for this light.
     * @param color a Vector specifying the color.
     */
    AmbientLight &in(const Vector &color);

    /**
     * Set the color for this light.
     * @param r/g/b RGB values
     */
    AmbientLight &in(float r, float g, float b);
};

}

#endif //RAYTRACER_AMBIENTLIGHT_H
