//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_AREALIGHT_H
#define RAYTRACER_AREALIGHT_H

#include <vector>

#include "light.h"
#include "common.h"

class AreaLight : public Light {
public:
    AreaLight(float x, float y, float z, float nx, float ny, float nz,
              float ux, float uy, float uz, float len, float r, float g, float b)
            : Light(r, g, b), _orig(x, y, z), _norm(nx, ny, nz), _u(ux, uy, uz), _len(len) {
        _norm.normalize();
        _u.normalize();
        _v = _u.cross(_norm);
        _v.normalize();
    }

    std::vector<Point> sample(int sampling_num);

    inline const Point &orig() const {
        return _orig;
    }

    inline const Vector &norm() const {
        return _norm;
    }

    inline const Vector &u() const {
        return _u;
    }

    inline const Vector &v() const {
        return _v;
    }

    inline float len() const {
        return _len;
    }

private:
    Point _orig;
    Vector _norm;
    Vector _u;
    Vector _v;
    float _len;
};


#endif //RAYTRACER_AREALIGHT_H
