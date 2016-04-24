//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H


#include "light.h"

class AmbientLight : public Light {
public:
    AmbientLight(float r, float g, float b) : Light{r, g, b} { }

    AmbientLight(const Vector &rgb) : Light{rgb} { }

    AmbientLight &in(const Vector &color);

    AmbientLight &in(float r, float g, float b);
};


#endif //RAYTRACER_AMBIENTLIGHT_H
