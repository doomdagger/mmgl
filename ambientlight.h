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
};


#endif //RAYTRACER_AMBIENTLIGHT_H
