//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_SCENE_CONFIG_H
#define RAYTRACER_SCENE_CONFIG_H

#include <algorithm>
#include <thread>

#include "mmgl/util/common.h"

namespace mmgl {

class SceneConfig {
public:
    friend class Scene;

    SceneConfig() : _render_flag{Render::BVH}, _bvh_mode{BVH::VOLUME_CUT},
                    _pixel_sampling_num{2}, _shadow_sampling_num{2}, _recursive_limit{5},
                    _thread_num{std::thread::hardware_concurrency()}, _partition_num{1000} { }

    size_t thread_num() const {
        return _thread_num;
    }

    void thread_num(int thread_num) {
        SceneConfig::_thread_num = thread_num;
    }

    size_t partition_num() const {
        return _partition_num;
    }

    void partition_num(int partition_num) {
        SceneConfig::_partition_num = std::min(static_cast<size_t>(partition_num),
                                               static_cast<size_t>(std::thread::hardware_concurrency()));
    }

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
    size_t _thread_num;
    size_t _partition_num;
};

}

#endif //RAYTRACER_SCENE_CONFIG_H
