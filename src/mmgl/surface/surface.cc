//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "mmgl/surface/surface.h"

namespace mmgl {

std::ostream &operator<<(std::ostream &os, const Surface &surface) {
    os << surface.to_string() << std::flush;
    return os;
}

}