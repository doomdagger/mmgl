//
// Created by lihe on 4/23/16.
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include <iostream>
#include <vector>
#include <ImfArray.h>
#include <ImfRgba.h>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <ImfRgbaFile.h>

#include "point.h"
#include "vector.h"
#include "ray.h"
#include "surface.h"
#include "light.h"
#include "pointlight.h"
#include "ambientlight.h"
#include "triangle.h"
#include "common.h"
#include "bvh_node.h"
#include "arealight.h"
#include "scene_config.h"

class Camera {
public:
    Camera(const Point &eye = Point(), float d = 0,
           const Vector &u = Vector(), const Vector &v = Vector(), const Vector &w = Vector(),
           int nx = 0, int ny = 0, float l = 0, float r = 0, float t = 0, float b = 0);

    void config(float x, float y, float z, float d, float dx, float dy, float dz,
                int nx, int ny, float iw, float ih);

    Ray project_pixel(float i, float j);

    void render(const std::vector<Surface *> &objects, const std::vector<Light *> &lights,
                const BVHNode *const parent, const SceneConfig &sceneConfig);

    Vector L(Ray &ray, int recursive_limit, const Surface *const object_id,
             const std::vector<Surface *> &objects, const std::vector<Light *> &lights,
             const BVHNode *const parent, const Render &flag, int s_sampling_num);

    std::pair<bool, Vector> blinn_phong(const Ray &pri_ray, const Point &light_pt, const Vector &light_cl,
                                        const Intersection &intersection,
                                        const Material &material, const std::vector<Surface *> &objects,
                                        const BVHNode *const parent,
                                        const Render &flag);

    void writeRgba(const std::string &);

    const Imf::Rgba *image() const;

    int width() const;

    int height() const;

    friend std::ostream &operator<<(std::ostream &os, const Camera &camera);

private:
    Point _eye;
    float _d;
    Vector _u, _v, _w;  // both normalized
    int _nx;
    int _ny;
    float _l, _r, _t, _b;
    Imf::Array2D<Imf::Rgba> _image;
};


#endif //RAYTRACER_CAMERA_H
