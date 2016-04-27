//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_SCENE_CONFIG_H
#define RAYTRACER_SCENE_CONFIG_H


#include "mmgl/util/common.h"

namespace mmgl {

class SceneConfig {
public:
    friend class Scene;

    SceneConfig() : _render_flag{Render::BVH}, _bvh_mode{BVH::VOLUME_CUT},
                    _pixel_sampling_num{2}, _shadow_sampling_num{2}, _recursive_limit{5} { }

    const Render &render_flag() const {
        return _render_flag;
    }

    void render_flag(const Render &render_flag) {
        SceneConfig::_render_flag = render_flag;
    }

    int pixel_sampling_num() const {
        return _pixel_sampling_num;
    }

    void pixel_sampling_num(int pixel_sampling_num) {
        SceneConfig::_pixel_sampling_num = pixel_sampling_num;
    }

    int shadow_sampling_num() const {
        return _shadow_sampling_num;
    }

    void shadow_sampling_num(int shadow_sampling_num) {
        SceneConfig::_shadow_sampling_num = shadow_sampling_num;
    }

    int recursive_limit() const {
        return _recursive_limit;
    }

    void recursive_limit(int recursive_limit) {
        SceneConfig::_recursive_limit = recursive_limit;
    }


    const BVH &bvh_mode() const {
        return _bvh_mode;
    }

    void bvh_mode(const BVH &bvh_mode) {
        _bvh_mode = bvh_mode;
    }

private:
    Render _render_flag;
    BVH _bvh_mode;
    int _pixel_sampling_num;
    int _shadow_sampling_num;
    int _recursive_limit;
};

}

#endif //RAYTRACER_SCENE_CONFIG_H
