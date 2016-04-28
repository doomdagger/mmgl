//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H


#include "mmgl/light/light.h"

namespace mmgl {

class AmbientLight : public Light {
public:
    AmbientLight(float r = 0, float g = 0, float b = 0) : Light{r, g, b} { }

    AmbientLight(const Vector &rgb) : Light{rgb} { }

    AmbientLight(const AmbientLight &light) : Light{light.color()} { }

    AmbientLight &in(const Vector &color);

    AmbientLight &in(float r, float g, float b);
};

}

#endif //RAYTRACER_AMBIENTLIGHT_H
