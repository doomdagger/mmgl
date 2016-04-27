//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "mmgl/light/ambientlight.h"

namespace mmgl {

AmbientLight &AmbientLight::in(const Vector &color) {
    Light::color(color);
    return *this;
}

AmbientLight &AmbientLight::in(float r, float g, float b) {
    Light::color(r, g, b);
    return *this;
}

}