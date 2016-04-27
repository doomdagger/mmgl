//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include <queue>

#include "mmgl/util/common.h"
#include "mmgl/surface/surface.h"
#include "mmgl/light/light.h"
#include "mmgl/core/camera.h"
#include "mmgl/util/scene_config.h"
#include "mmgl/surface/bvh_node.h"
#include "mmgl/surface/sphere.h"

namespace mmgl {

class Scene {
public:
    Scene() : _surfaces{}, _lights{}, _camera{}, config{} { }

    Scene(const std::string &scene_file);

    inline const Camera &camera() const {
        return _camera;
    }

    void configCamera(float x, float y, float z, float dx, float dy, float dz, float d,
                      float iw, float ih, int nx, int ny);

    void render();

    void save(const std::string &file_path) const;

    Sphere &sphere(float x = .0f, float y = .0f, float z = .0f, float radius = .0f,
                   const Material &material = Material{});

    Triangle &triangle(float x1 = .0f, float y1 = .0f, float z1 = .0f,
                       float x2 = .0f, float y2 = .0f, float z2 = .0f,
                       float x3 = .0f, float y3 = .0f, float z3 = .0f,
                       const Material &material = Material{});

    PointLight &pointLight(float x = .0f, float y = .0f, float z = .0f,
                           float r = .0f, float g = .0f, float b = .0f);

    AreaLight &areaLight(float x = .0f, float y = .0f, float z = .0f, float nx = .0f, float ny = .0f, float nz = .0f,
                         float ux = .0f, float uy = .0f, float uz = .0f, float len = .0f, float r = .0f, float g = .0f,
                         float b = .0f);

    AmbientLight &ambientLight(float r = .0f, float g = .0f, float b = .0f);

    ~Scene();

    // public member field config for easy access
    SceneConfig config;
private:
    std::vector<Surface *> _surfaces;
    std::vector<Light *> _lights;

    Camera _camera;
};  // class Scene

}   // namespace mmgl




#endif //RAYTRACER_SCENE_H
