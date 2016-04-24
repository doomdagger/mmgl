//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include <queue>

#include "common.h"
#include "surface.h"
#include "light.h"
#include "camera.h"
#include "scene_config.h"
#include "bvh_node.h"
#include "sphere.h"


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

    Sphere &sphere(const Point &central = Point{}, float radius = .0f,
                   const Material &material = Material{});

    Triangle &triangle(float x1 = .0f, float y1 = .0f, float z1 = .0f,
                       float x2 = .0f, float y2 = .0f, float z2 = .0f,
                       float x3 = .0f, float y3 = .0f, float z3 = .0f,
                       const Material &material = Material{});

    Triangle &triangle(const Point &p1 = Point{}, const Point &p2 = Point{}, const Point &p3 = Point{},
                       const Material &material = Material{});

    PointLight &pointLight(float x = .0f, float y = .0f, float z = .0f,
                           float r = .0f, float g = .0f, float b = .0f);

    PointLight &pointLight(const Point &position = Point{}, const Vector &rgb = Vector{});

    AreaLight &areaLight(float x = .0f, float y = .0f, float z = .0f, float nx = .0f, float ny = .0f, float nz = .0f,
                         float ux = .0f, float uy = .0f, float uz = .0f, float len = .0f, float r = .0f, float g = .0f,
                         float b = .0f);

    AreaLight &areaLight(const Point &position = Point{}, const Vector &normal = Vector{},
                         const Vector &u_vector = Vector{}, float len = .0f, const Vector &rgb = Vector{});

    AmbientLight &ambientLight(float r = .0f, float g = .0f, float b = .0f);

    AmbientLight &ambientLight(const Vector &rgb = Vector{});

    ~Scene();

    // public member field config for easy access
    SceneConfig config;
private:
    std::vector<Surface *> _surfaces;
    std::vector<Light *> _lights;

    Camera _camera;
};


#endif //RAYTRACER_SCENE_H
