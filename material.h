//
// Created by lihe on 4/22/16.
//

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include "vector.h"

class Material {
public:

    Material(float dr = 0, float dg = 0, float db = 0,
             float sr = 0, float sg = 0, float sb = 0,
             float ir = 0, float ig = 0, float ib = 0,
             float r = 0) : _kd{dr, dg, db}, _ks{sr, sg, sb}, _ki{ir, ig, ib},
                            _r(r) { }


    inline const Vector &kd() const {
        return _kd;
    }

    inline const Vector &ks() const {
        return _ks;
    }

    inline const Vector &ki() const {
        return _ki;
    }

    inline bool isReflective() const {
        return _ki.x() || _ki.y() || _ki.z();
    }

    inline float r() const {
        return _r;
    }

private:
    Vector _kd;
    Vector _ks;
    Vector _ki;
    float _r;
};

#endif //RAYTRACER_MATERIAL_H
