//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H


#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <utility>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <future>
#include <functional>

#include "mmgl/util/point.h"
#include "mmgl/util/vector.h"
#include "mmgl/surface/ray.h"
#include "mmgl/surface/surface.h"
#include "mmgl/light/light.h"
#include "mmgl/light/pointlight.h"
#include "mmgl/light/ambientlight.h"
#include "mmgl/surface/triangle.h"
#include "mmgl/util/common.h"
#include "mmgl/surface/bvh_node.h"
#include "mmgl/light/arealight.h"
#include "mmgl/util/scene_config.h"
#include "mmgl/util/image.h"
#include "mmgl/util/thread_pool.h"

/**
 * The mmgl namespace contains all classes, aliases, enumerations, and functions. Users of the MMGL library should use this namespace to access the graphics constructs.
 */
namespace mmgl {

/**
 * The Camera class defines the viewpoint, image sizes, and so on. It is used in a scene object for rendering the objects in that scene.
 */
class Camera {
public:

    /**
     * Constructer for Camera that sets all camera parameters. The camera uses default parameters where most values are set to 0.
     * Scene objet will initialize this in its construtor.
     *
     * @param eye Position of the camera or the viewpoint.
     * @param nx Picture size in x dimension.
     * @param ny Picture size in y dimension.
     */
    Camera(const Point &eye = Point(), float d = 0,
           const Vector &u = Vector(), const Vector &v = Vector(), const Vector &w = Vector(),
           int nx = 0, int ny = 0, float l = 0, float r = 0, float t = 0, float b = 0);

    /**
     * A helper function for configuring all Camera parameters.
     *
     * @param x Position of the camera in x dimension.
     * @param y Position of the camera in y dimension.
     * @param z Position of the camera in z dimension.
     * @param d Focal length.
     * @param dx Facing direction in x.
     * @param dy Facing direction in y.
     * @param dz Facing direction in z.
     */
    void config(float x, float y, float z, float d, float dx, float dy, float dz,
                int nx, int ny, float iw, float ih);

    /**
     * Project pixel to a Ray object.
     * @param i In x direction.
     * @param j In y direction.
     */
    Ray project_pixel(float i, float j);

    /**
     * Set the position of the camera, using three float positions.
     * Return a reference to the same project, so multiple configs can be chained together.
     */
    Camera &at(float x, float y, float z);

    /**
     * Set the camera position using a Point object.
     */
    Camera &at(const Point &point);

    /**
     * Set the focal length of the camera.
     */
    Camera &focal_length(float d);

    /**
     * Set the facing direction using three floats.
     */
    Camera &facing(float dx, float dy, float dz);

    /**
     * Set the facing direction of the camera using a direction of type Vector.
     */
    Camera &facing(const Vector &dir);

    /**
     * Set the view range using two floats.
     */
    Camera &view_range(float iw, float ih);

    /**
     * Set the image size using two ints.
     * @param nx Size in the x direction.
     * @param ny Size in the y direction.
     */
    Camera &image_size(int nx, int ny);

    /**
     * Render function called inside Scene class. Users of the library don't need to call this directly.
     */
    void render(const std::vector<Surface *> &objects, const std::vector<Light *> &lights,
                const BVHNode *const parent, const SceneConfig &sceneConfig);

    void writeRgba(const std::string &) const;

    inline int width() const {
        return _nx;
    }

    inline int height() const {
        return _ny;
    }

    inline const Point &eye() const {
        return _eye;
    }

    inline const Image &image() const {
        return _image;
    }

    /**
     * Return a handle to the rendering results, called in Scene.
     */
    inline const RenderResult& handle() const {
        return _image.handle();
    }

    friend std::ostream &operator<<(std::ostream &os, const Camera &camera);

private:
    void render_partition(const size_t partition_id, const size_t partition_size,
                          const std::vector<Surface *> &objects, const std::vector<Light *> &lights,
                          const BVHNode *const parent, const SceneConfig &sceneConfig);

    Vector render_pixel(int x, int y, const std::vector<Surface *> &objects, const std::vector<Light *> &lights,
                        const BVHNode *const parent, const SceneConfig &sceneConfig,
                        const std::function<float()> &rand_float);

    Vector L(Ray &ray, int recursive_limit, const Surface *const object_id,
             const std::vector<Surface *> &objects, const std::vector<Light *> &lights,
             const BVHNode *const parent, const Render &flag, int s_sampling_nu,
             const std::function<float()> &rand_float);

    std::pair<bool, Vector> blinn_phong(const Ray &pri_ray, const Point &light_pt, const Vector &light_cl,
                                        const Intersection &intersection,
                                        const Material &material, const std::vector<Surface *> &objects,
                                        const BVHNode *const parent,
                                        const Render &flag);

    Point _eye;
    float _d;
    Vector _u, _v, _w;  // both normalized
    int _nx;
    int _ny;
    float _l, _r, _t, _b;
    Image _image;
};

}

#endif //RAYTRACER_CAMERA_H
