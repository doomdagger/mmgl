//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "mmgl/light/pointlight.h"

namespace mmgl {

PointLight &PointLight::in(const Vector &color) {
    Light::color(color);
    return *this;
}

PointLight &PointLight::in(float r, float g, float b) {
    Light::color(r, g, b);
    return *this;
}

PointLight &PointLight::at(const Point &position) {
    _orig.x(position.x());
    _orig.y(position.y());
    _orig.z(position.z());
    return *this;
}

PointLight &PointLight::at(float x, float y, float z) {
    _orig.x(x);
    _orig.y(y);
    _orig.z(z);
    return *this;
}

}