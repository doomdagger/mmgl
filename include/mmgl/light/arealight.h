//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_AREALIGHT_H
#define RAYTRACER_AREALIGHT_H

#include <functional>
#include <vector>

#include "mmgl/light/light.h"
#include "mmgl/util/common.h"

namespace mmgl {

/**
 * This class is for an arealight used in the scene.
 * Derived from Light base class.
 */
class AreaLight : public Light {
public:
    AreaLight(float x, float y, float z, float nx, float ny, float nz,
              float ux, float uy, float uz, float len, float r, float g, float b)
            : Light(r, g, b), _orig(x, y, z), _norm(nx, ny, nz), _u(ux, uy, uz), _len(len) {
        init();
    }

    AreaLight(const Point &position, const Vector &normal, const Vector &u_vector, float len,
              const Vector &rgb) : Light(rgb), _orig(position), _norm(normal), _u(u_vector), _len(len) {
        init();
    }

    std::vector<Point> sample(int sampling_num, const std::function<float()> &rand_float);

    /**
     * Set the color of this arealight.
     * @param color a Vector of RGB values.
     */
    AreaLight &in(const Vector &color);

    /**
     * Set the color of this arealight.
     * @param r/g/b RBG values.
     */
    AreaLight &in(float r, float g, float b);

    /**
     * Set the position of this arealight.
     * @param position A point specifying the position
     */
    AreaLight &at(const Point &position);

    /**
     * Set the position of this arealight.
     * @param x/y/z A point(x, y, z) specifying the position
     */
    AreaLight &at(float x, float y, float z);

    /**
     * Set the facing of this arealight.
     * @param norm A Vector specifying the facing
     */
    AreaLight &facing(const Vector &norm);

    /**
     * Set the facing of this arealight.
     * @param x/y/z A Vector(x, y, z) specifying the facing
     */
    AreaLight &facing(float x, float y, float z);

    /**
     * Set the forward of this arealight.
     * @param u A Vector specifying the forward
     */
    AreaLight &forward(const Vector &u);

    /**
     * Set the forward of this arealight.
     * @param x/y/z A Specify the forward using x, y, z.
     */
    AreaLight &forward(float x, float y, float z);

    /**
     * Set the length of this arealight.
     * @param len Type is float.
     */
    AreaLight &length(float len);

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
    void init() {
        _norm.normalize();
        _u.normalize();
        _v = _u.cross(_norm);
        _v.normalize();
    }

    Point _orig;
    Vector _norm;
    Vector _u;
    Vector _v;
    float _len;
};

}

#endif //RAYTRACER_AREALIGHT_H
