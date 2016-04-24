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


class Scene {
public:
    Scene() : _surfaces{}, _lights{}, _camera{} {}

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

    void camera(const Camera &camera) {
        _camera = camera;
    }

    void render();

    // public member field config for easy access
    SceneConfig config;
private:
    std::map<unsigned long, Surface *> _surfaces;
    std::map<unsigned long, Light *> _lights;

    Camera _camera;
};


#endif //RAYTRACER_SCENE_H
