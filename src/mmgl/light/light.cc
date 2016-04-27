//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "mmgl/light/light.h"

void Light::color(const Vector &color) {
    _color.x(color.x());
    _color.y(color.y());
    _color.z(color.z());
}

void Light::color(float r, float g, float b) {
    _color.x(r);
    _color.y(g);
    _color.z(b);
}
