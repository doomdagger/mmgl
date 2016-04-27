//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "surface/sphere.h"

Sphere::Sphere(float x, float y, float z, float r) : _origin{x, y, z}, _radius{r} {
    init();
}

Sphere::Sphere(const Point &origin, float radius) : _origin{origin}, _radius{radius} {
    init();
}

bool Sphere::intersect(Ray &ray, const Render &flag) const {
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

    Vector oo = ray._origin - _origin;
    Vector r_dir = ray._dir;
    float r_oo = r_dir.dot(oo);
    float r_r = r_dir.dot(r_dir);
    float discriminant = r_oo * r_oo - r_r * (oo.dot(oo) - _radius * _radius);
    if (discriminant >= 0) {
        // get the parameterization of the intersection point
        float t;
        if (discriminant == 0) {
            t = -r_oo / r_r;
        } else {
            float t1 = (-r_oo + sqrtf(discriminant)) / r_r;
            float t2 = (-r_oo - sqrtf(discriminant)) / r_r;
            t = (t1 < t2 ? t1 : t2);
        }
        if (t < 0)
            return false;
        if (ray.updatable(t)) {
            Point inter_p = ray._origin + ray._dir * t;
            Vector norm = inter_p - _origin;
            norm.normalize();
            ray.intersection(Intersection(t, inter_p, norm, this));
        }
        return true;
    } else {
        return false;
    }
}

std::string Sphere::to_string() const {
    std::stringstream os;
    os << "Sphere:\n";
    os << "\torigin: " << _origin << "\n";
    os << "\tradius: " << _radius << std::flush;
    return os.str();
}

Sphere &Sphere::at(const Point &central) {
    _origin._x = central._x;
    _origin._y = central._y;
    _origin._z = central._z;
    init();
    return *this;
}

Sphere &Sphere::at(float x, float y, float z) {
    _origin._x = x;
    _origin._y = y;
    _origin._z = z;
    init();
    return *this;
}

Sphere &Sphere::radius(float radius) {
    _radius = radius;
    init();
    return *this;
}

Sphere &Sphere::made_of(const Material &material) {
    Surface::material(material);
    return *this;
}
