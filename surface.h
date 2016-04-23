//
// Created by lihe on 4/22/16.
//

#ifndef RAYTRACER_SURFACE_H
#define RAYTRACER_SURFACE_H


#include "material.h"
#include "bbox.h"

class Surface {
public:

private:
    Material _material;
    BBox _box;
};


#endif //RAYTRACER_SURFACE_H
