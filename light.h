//
// Created by lihe on 4/23/16.
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "vector.h"

class Light {
public:
    Light(float r = 0, float g = 0, float b = 0) : _color{r, g, b} { }

    inline const Vector &color() const {
        return _color;
    }

    virtual ~Light() { };
private:
    Vector _color;
};


#endif //RAYTRACER_LIGHT_H
