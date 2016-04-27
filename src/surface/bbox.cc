//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "surface/bbox.h"

std::pair<bool, float> BBox::intersect(const Ray &ray, bool isNode) const {
    std::pair<bool, float> ret{false, .0f};
    const Vector &ray_dir = ray._dir;
    const Point &ray_orig = ray._origin;
    float tx_min, tx_max, ty_min, ty_max, tz_min, tz_max, t_min, t_max;
    // tx_min, tx_max
    if (ray_dir._x < 0) {
        tx_max = (_min._x - ray_orig._x) / ray_dir._x;
        tx_min = (_max._x - ray_orig._x) / ray_dir._x;
    } else if (ray_dir._x > 0) {
        tx_max = (_max._x - ray_orig._x) / ray_dir._x;
        tx_min = (_min._x - ray_orig._x) / ray_dir._x;
    } else {
        if (_min._x > ray_orig._x || ray_orig._x > _max._x) {
            return std::move(ret);
        } else {
            tx_max = std::numeric_limits<float>::infinity();
            tx_min = -std::numeric_limits<float>::infinity();
        }
    }
    // ty_min, ty_max
    if (ray_dir._y < 0) {
        ty_max = (_min._y - ray_orig._y) / ray_dir._y;
        ty_min = (_max._y - ray_orig._y) / ray_dir._y;
    } else if (ray_dir._y > 0) {
        ty_max = (_max._y - ray_orig._y) / ray_dir._y;
        ty_min = (_min._y - ray_orig._y) / ray_dir._y;
    } else {
        if (_min._y > ray_orig._y || ray_orig._y > _max._y) {
            return std::move(ret);
        } else {
            ty_max = std::numeric_limits<float>::infinity();
            ty_min = -std::numeric_limits<float>::infinity();
        }
    }
    // tz_min, tz_max
    if (ray_dir._z < 0) {
        tz_max = (_min._z - ray_orig._z) / ray_dir._z;
        tz_min = (_max._z - ray_orig._z) / ray_dir._z;
    } else if (ray_dir._z > 0) {
        tz_max = (_max._z - ray_orig._z) / ray_dir._z;
        tz_min = (_min._z - ray_orig._z) / ray_dir._z;
    } else {
        if (_min._z > ray_orig._z || ray_orig._z > _max._z) {
            return std::move(ret);
        } else {
            tz_max = std::numeric_limits<float>::infinity();
            tz_min = -std::numeric_limits<float>::infinity();
        }
    }
    t_min = std::fmaxf(std::fmaxf(tx_min, ty_min), tz_min);
    t_max = std::fminf(std::fminf(tx_max, ty_max), tz_max);
    // very important here, my trick
    if (isNode) {
        if (t_max < .0f) {
            return std::move(ret);
        }
    } else {
        if (t_min < -10.f) {
            return std::move(ret);
        }
    }

    // for triangle, the bounding box might be a thin layer
    ret.first = t_min < t_max;
    ret.second = t_min;

    return std::move(ret);
}

void BBox::box(float x_min, float y_min, float z_min, float x_max, float y_max, float z_max) {
    _min._x = x_min - BOUNDING;
    _min._y = y_min - BOUNDING;
    _min._z = z_min - BOUNDING;

    _max._x = x_max + BOUNDING;
    _max._y = y_max + BOUNDING;
    _max._z = z_max + BOUNDING;
}

Vector BBox::normal(const Point &inter_p) const {
    Vector ret(.0f, .0f, .0f);

    if (fabsf(inter_p._x - _min._x) < TOLERANCE) {
        ret._x = -1;
    } else if (fabsf(inter_p._x - _max._x) < TOLERANCE) {
        ret._x = 1;
    } else if (fabsf(inter_p._y - _min._y) < TOLERANCE) {
        ret._y = -1;
    } else if (fabsf(inter_p._y - _max._y) < TOLERANCE) {
        ret._y = 1;
    } else if (fabsf(inter_p._z - _min._z) < TOLERANCE) {
        ret._z = -1;
    } else if (fabsf(inter_p._z - _max._z) < TOLERANCE) {
        ret._z = 1;
    }
    return std::move(ret);
}
