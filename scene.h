//
// Created by lihe on 4/22/16.
//

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include <vector>
#include <map>
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
    Scene() : _surfaces{}, _lights{}, _camera{}, config{} {}

    Scene(const std::string &scene_file);

    const std::vector<Surface *> surfaces() const {
        std::vector<Surface *> ret;
        for (auto &elem : _surfaces) {
            ret.push_back(elem.second);
        }
        return std::move(ret);
    }

    const std::vector<Light *> lights() const {
        std::vector<Light *> ret;
        for (auto &elem : _lights) {
            ret.push_back(elem.second);
        }
        return std::move(ret);
    }

    const Camera &camera() const {
        return _camera;
    }

    void render();

    unsigned long NewSphere(float x, float y, float z, float radius, const Material &material);

    unsigned long NewTriangle(float x1, float y1, float z1,
                              float x2, float y2, float z2,
                              float x3, float y3, float z3, const Material &material);

    unsigned long NewPointLight(float x, float y, float z,
                                float r, float g, float b);

    unsigned long NewAreaLight(float x, float y, float z, float nx, float ny, float nz,
                               float ux, float uy, float uz, float len, float r, float g, float b);

    unsigned long NewAmbientLight(float r, float g, float b);

    // public member field config for easy access
    SceneConfig config;
private:
    std::map<unsigned long, Surface *> _surfaces;
    std::map<unsigned long, Light *> _lights;

    unsigned long _surface_id = 0;
    unsigned long _light_id = 0;

    Camera _camera;
};


#endif //RAYTRACER_SCENE_H
