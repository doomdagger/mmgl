//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "point.h"

Point::Point(float x, float y, float z) : _x{x}, _y{y}, _z{z} { }

std::ostream &operator<<(std::ostream &os, const Point &p) {
    os << "Point: " << p.x() << " " << p.y() << " " << p.z() << std::flush;
    return os;
}
