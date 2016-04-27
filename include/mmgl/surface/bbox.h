//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_BBOX_H
#define RAYTRACER_BBOX_H

#include <map>
#include <limits>

#include "mmgl/util/vector.h"
#include "mmgl/util/point.h"
#include "mmgl/surface/ray.h"

#define TOLERANCE 0.001f
#define BOUNDING 0.002f

namespace mmgl {

class BBox {
public:
    std::pair<bool, float> intersect(const Ray &ray, bool isNode) const;

    Vector normal(const Point &inter_p) const;

    BBox(float x_min = .0f, float y_min = .0f, float z_min = .0f,
         float x_max = .0f, float y_max = .0f, float z_max = .0f) : _min{x_min, y_min, z_min},
                                                                    _max{x_max, y_max, z_max} { }

    void box(float x_min, float y_min, float z_min,
             float x_max, float y_max, float z_max);

    inline const Point &min() const {
        return _min;
    }

    inline const Point &max() const {
        return _max;
    }

private:
    Point _min, _max;
};

}

#endif //RAYTRACER_BBOX_H
