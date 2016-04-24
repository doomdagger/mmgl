//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H


#include "vector.h"

class Light {
public:
    Light(float r = 0, float g = 0, float b = 0) : _color{r, g, b} { }

    Light(const Vector &rgb) : _color{rgb} { }

    inline const Vector &color() const {
        return _color;
    }

    virtual ~Light() { };
private:
    Vector _color;
};


#endif //RAYTRACER_LIGHT_H
