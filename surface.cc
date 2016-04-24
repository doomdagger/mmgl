//
// Created by lihe on 4/22/16.
//

#include "surface.h"

std::ostream &operator<<(std::ostream &os, const Surface &surface) {
    os << surface.to_string() << std::flush;
    return os;
}
