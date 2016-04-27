//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "mmgl/surface/triangle.h"

namespace mmgl {

Triangle::Triangle(float x1, float y1, float z1,
                   float x2, float y2, float z2,
                   float x3, float y3, float z3) : _p1{x1, y1, z1}, _p2{x2, y2, z2}, _p3{x3, y3, z3} {
    init();
}

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3) : _p1{p1}, _p2{p2}, _p3{p3} {
    init();
}

bool Triangle::intersect(Ray &ray, const Render &flag) const {
    std::pair<bool, float> box_hit = box_intersect(ray);
    if (!box_hit.first) {
        return false;
    }
    if (flag == Render::BVH_BBOX_ONLY || flag == Render::BBOX_ONLY) {
        if (ray.updatable(box_hit.second)) {
            Point inter_p = ray._origin + ray._dir * box_hit.second;
            Vector norm = box_normal(inter_p);
            ray.intersection(Intersection(box_hit.second, inter_p, norm, this));
        }
        return true;
    }

    if (ray.has_intersect() && ray.intersection().t() < box_hit.second) {
        // skip intersection computation if bbox distance is larger than closest intersection point
        return true;
    }

    // method from book: fundamentals of computer graphics
    float g, h, i, j, k, l, ei_hf, gf_di, dh_eg, ak_jb, jc_al, bl_kc;
    g = ray._dir._x;
    h = ray._dir._y;
    i = ray._dir._z;
    j = _p1._x - ray._origin._x;
    k = _p1._y - ray._origin._y;
    l = _p1._z - ray._origin._z;
    ei_hf = _e * i - h * _f;
    gf_di = g * _f - _d * i;
    dh_eg = _d * h - _e * g;
    ak_jb = _a * k - j * _b;
    jc_al = j * _c - _a * l;
    bl_kc = _b * l - k * _c;
    float beta, gamma, t, M;
    M = _a * ei_hf + _b * gf_di + _c * dh_eg;
    // we need the linear solution can have some conditions for early termination
    t = -(_f * ak_jb + _e * jc_al + _d * bl_kc) / M;
    if (t < 0.00005f)
        return false;
    gamma = (i * ak_jb + h * jc_al + g * bl_kc) / M;
    if (gamma < 0 || gamma > 1)
        return false;
    beta = (j * ei_hf + k * gf_di + l * dh_eg) / M;
    if (beta < 0 || beta > (1 - gamma)) {
        return false;
    }
    if (ray.updatable(t)) {
        // if we survive here, compute the intersection point
        Point inter_p = ray._origin + ray._dir * t;
        ray.intersection(Intersection{t, inter_p, _norm, this});
    }
    return true;
}

std::string Triangle::to_string() const {
    std::stringstream os;
    os << "Triangle:\n";
    os << "\tp1: " << _p1 << "\n";
    os << "\tp2: " << _p2 << "\n";
    os << "\tp3: " << _p3 << std::flush;
    return os.str();
}

Triangle &Triangle::point_one(const Point &p1) {
    _p1._x = p1._x;
    _p1._y = p1._y;
    _p1._z = p1._z;
    init();
    return *this;
}

Triangle &Triangle::point_two(const Point &p2) {
    _p2._x = p2._x;
    _p2._y = p2._y;
    _p2._z = p2._z;
    init();
    return *this;
}

Triangle &Triangle::point_three(const Point &p3) {
    _p3._x = p3._x;
    _p3._y = p3._y;
    _p3._z = p3._z;
    init();
    return *this;
}

Triangle &Triangle::point_one(float x, float y, float z) {
    _p1._x = x;
    _p1._y = y;
    _p1._z = z;
    init();
    return *this;
}

Triangle &Triangle::point_two(float x, float y, float z) {
    _p2._x = x;
    _p2._y = y;
    _p2._z = z;
    init();
    return *this;
}

Triangle &Triangle::point_three(float x, float y, float z) {
    _p3._x = x;
    _p3._y = y;
    _p3._z = z;
    init();
    return *this;
}

Triangle &Triangle::made_of(const Material &material) {
    Surface::material(material);
    return *this;
}

}