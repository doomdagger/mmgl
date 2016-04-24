//
// Created by lihe on 4/23/16.
//

#ifndef RAYTRACER_AMBIENTLIGHT_H
#define RAYTRACER_AMBIENTLIGHT_H


#include "light.h"

class AmbientLight : public Light {
public:
    AmbientLight(float r, float g, float b) : Light{r, g, b} { }
};


#endif //RAYTRACER_AMBIENTLIGHT_H
