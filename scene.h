//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
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
    Scene() : _surfaces{}, _lights{}, _camera{}, config{} { }

    Scene(const std::string &scene_file);

    const std::vector<Surface *> surfaces() const;

    const std::vector<Light *> lights() const;

    inline const Camera &camera() const {
        return _camera;
    }

    inline Surface *surface(unsigned long id) {
        return _surfaces[id];
    }

    inline Light *light(unsigned long id) {
        return _lights[id];
    }

    void configCamera(float x, float y, float z, float d, float dx, float dy, float dz,
                      int nx, int ny, float iw, float ih);

    void render();

    void save(const std::string &file_path) const;

    unsigned long sphere(float x, float y, float z, float radius, const Material &material = Material{});

    unsigned long triangle(float x1, float y1, float z1,
                           float x2, float y2, float z2,
                           float x3, float y3, float z3, const Material &material = Material{});

    unsigned long pointLight(float x, float y, float z,
                             float r, float g, float b);

    unsigned long areaLight(float x, float y, float z, float nx, float ny, float nz,
                            float ux, float uy, float uz, float len, float r, float g, float b);

    unsigned long ambientLight(float r, float g, float b);



    ~Scene();

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
