//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_SCENE_CONFIG_H
#define RAYTRACER_SCENE_CONFIG_H

#include <algorithm>
#include <cassert>
#include <thread>

#include "mmgl/util/common.h"

namespace mmgl {

class SceneConfig {
public:
    // friend class Scene;

    SceneConfig() : _render_flag{Render::BVH}, _bvh_mode{BVH::VOLUME_CUT},
                    _pixel_sampling_num{2}, _shadow_sampling_num{2}, _recursive_limit{5},
                    _thread_num{std::thread::hardware_concurrency()}, _partition_num{1000} { }

    unsigned thread_num() const {
        return _thread_num;
    }

    SceneConfig &thread_num(unsigned thread_num) {
        _thread_num = thread_num;
        assert(_thread_num > 0);
        return *this;
    }

    unsigned partition_num() const {
        return _partition_num;
    }

    SceneConfig &partition_num(unsigned partition_num) {
        _partition_num = partition_num;
        assert(_partition_num > 0);
        // _thread_num = std::min(partition_num, std::thread::hardware_concurrency());
        return *this;
    }

    const Render &render_flag() const {
        return _render_flag;
    }

    SceneConfig &render_flag(const Render &render_flag) {
        _render_flag = render_flag;
        return *this;
    }

    int pixel_sampling_num() const {
        return _pixel_sampling_num;
    }

    SceneConfig &pixel_sampling_num(int pixel_sampling_num) {
        _pixel_sampling_num = pixel_sampling_num;
        return *this;
    }

    int shadow_sampling_num() const {
        return _shadow_sampling_num;
    }

    SceneConfig &shadow_sampling_num(int shadow_sampling_num) {
        _shadow_sampling_num = shadow_sampling_num;
        return *this;
    }

    int recursive_limit() const {
        return _recursive_limit;
    }

    SceneConfig &recursive_limit(int recursive_limit) {
        _recursive_limit = recursive_limit;
        return *this;
    }

    const BVH &bvh_mode() const {
        return _bvh_mode;
    }

    SceneConfig &bvh_mode(const BVH &bvh_mode) {
        _bvh_mode = bvh_mode;
        return *this;
    }

private:
    Render _render_flag;
    BVH _bvh_mode;
    int _pixel_sampling_num;
    int _shadow_sampling_num;
    int _recursive_limit;
    unsigned _thread_num;
    unsigned _partition_num;
};

}

#endif //RAYTRACER_SCENE_CONFIG_H
