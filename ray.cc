//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "ray.h"

Ray::Ray(const Point &point, const Vector &vector) : _origin{point}, _dir{vector}, _has_intersect{false},
                                                     _intersection{} { }

Ray::Ray(float pos_x, float pos_y, float pos_z,
         float dir_x, float dir_y, float dir_z) : _origin{pos_x, pos_y, pos_z}, _dir{dir_x, dir_y, dir_z},
                                                  _has_intersect{false}, _intersection{} { }

std::ostream &operator<<(std::ostream &os, const Ray &ray) {
    os << "Ray:\n";
    os << "\t" << ray.origin() << "\n";
    os << "\t" << ray.dir() << std::endl;
    return os;
}


bool Ray::has_block(float max) const {
    if (!has_intersect()) {
        return false;
    } else {
        return _intersection.t() < max;
    }
}

bool Ray::updatable(float t) const {
    if (_has_intersect) {
        return (t > EPS && t < _intersection.t());
    } else {
        return t > EPS;
    }
}