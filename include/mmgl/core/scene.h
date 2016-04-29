//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include <queue>
#include <chrono>

#include "mmgl/util/common.h"
#include "mmgl/surface/surface.h"
#include "mmgl/light/light.h"
#include "mmgl/core/camera.h"
#include "mmgl/util/scene_config.h"
#include "mmgl/surface/bvh_node.h"
#include "mmgl/surface/sphere.h"
#include "mmgl/light/pointlight.h"
#include "mmgl/light/ambientlight.h"
#include "mmgl/light/arealight.h"

namespace mmgl {

/**
 * Scene class decribes the objects to be rendered. Lights are also used in a Scene object.
 * The configuration parameters are in _config of type SceneConfig.
 * The Camera object _camera is used for rendering.
 */
class Scene {
public:
    /**
     * Default and minimal Scene constructor. It also sets a default camera for convenient usage.
     */
    Scene() : _surfaces{}, _lights{}, _camera{}, _config{} {
        configCamera(10, 10, 10, -1, -1, -1, 100, 100, 100, 1000, 1000);
    }

    /**
     * Construct a scene from a file. This parses a text file describing all the objects used in a scene.
     * @param scene_file Name of the file containing scene objects and lights.
     */
    Scene(const std::string &scene_file);

    /**
     * Get the configuration of the scene.
     * @return _config A reference to SceneConfig object.
     */
    inline SceneConfig &config() {
        return _config;
    }

    /**
     * Get the camera of this scene.
     */
    inline Camera &camera() {
        return _camera;
    }

    /**
     * Get a handle to the rendering results, which is a reference to the RenderResult type.
     */
    inline const RenderResult& handle() const {
        return _camera.handle();
    }

    /**
     * Performs rendering.
     */
    void render();

    /**
     * Save the rendering results as a bmp picture in the specied file.
     * @param file_path The output bmp picture file.
     */
    void save(const std::string &file_path) const;

    void configCamera(float x, float y, float z, float dx, float dy, float dz, float d,
                      float iw, float ih, int nx, int ny);

    /**
     * Add a new sphere in the current scene.
     * Return a reference so the configurations can be chained together.
     * Default size is unit size and at the origin posision.
     */
    Sphere &sphere(float x = .0f, float y = .0f, float z = .0f, float radius = 1.0f,
                   const Material &material = Material{});

    /**
     * Add a new triangle in the current scene.
     * Return a reference so the configurations can be chained together.
     */
    Triangle &triangle(float x1 = 1.0f, float y1 = .0f, float z1 = .0f,
                       float x2 = .0f, float y2 = 1.0f, float z2 = .0f,
                       float x3 = .0f, float y3 = .0f, float z3 = 1.0f,
                       const Material &material = Material{});

    /**
     * Add a point light to the current scene.
     */
    PointLight &pointLight(float x = 100.0f, float y = 100.0f, float z = 100.0f,
                           float r = 1.0f, float g = 1.0f, float b = 1.0f);

    /**
     * Add an area light to the current scene.
     */
    AreaLight &areaLight(float x = 100.0f, float y = 100.0f, float z = 100.0f, float nx = .0f, float ny = -1.0f, float nz = .0f,
                         float ux = 1.0f, float uy = .0f, float uz = .0f, float len = 2.0f, float r = 3000.0f, float g = 3000.0f,
                         float b = 3000.0f);

    /**
     * Add an ambient light to the current scene.
     */
    AmbientLight &ambientLight(float r = .03f, float g = .03f, float b = .03f);

    ~Scene();

private:
    std::vector<Surface *> _surfaces;
    std::vector<Light *> _lights;
    Camera _camera;
    SceneConfig _config;

};  // class Scene

}   // namespace mmgl




#endif //RAYTRACER_SCENE_H
