//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "mmgl/light/arealight.h"

#include <functional>

namespace mmgl {

std::vector<Point> AreaLight::sample(int sampling_num, const std::function<float()> &rand_float) {
    std::vector<Point> samples;

    if (sampling_num < 1) {
        std::cerr << "Sampling Number in Area Light is less than 1! Automatically make it 1 then" << std::endl;
        sampling_num = 1;
    }

    float half_len = _len * 0.5f;
    float step_size = _len / sampling_num;
    for (int p = 0; p < sampling_num; p++) {
        for (int q = 0; q < sampling_num; q++) {
            // stratified
            Point sample = _orig + _u * (q * step_size + rand_float() * step_size - half_len) +
                           _v * (p * step_size + rand_float() * step_size - half_len);
            samples.push_back(std::move(sample));
        }
    }
    return std::move(samples);
}

AreaLight &AreaLight::in(const Vector &color) {
    Light::color(color);
    return *this;
}

AreaLight &AreaLight::in(float r, float g, float b) {
    Light::color(r, g, b);
    return *this;
}

AreaLight &AreaLight::at(const Point &position) {
    _orig.x(position.x());
    _orig.y(position.y());
    _orig.z(position.z());
    return *this;
}

AreaLight &AreaLight::at(float x, float y, float z) {
    _orig.x(x);
    _orig.y(y);
    _orig.z(z);
    return *this;
}

AreaLight &AreaLight::facing(const Vector &norm) {
    _norm.x(norm.x());
    _norm.y(norm.y());
    _norm.z(norm.z());
    init();
    return *this;
}

AreaLight &AreaLight::facing(float x, float y, float z) {
    _norm.x(x);
    _norm.y(y);
    _norm.z(z);
    init();
    return *this;
}

AreaLight &AreaLight::forward(const Vector &u) {
    _u.x(u.x());
    _u.y(u.y());
    _u.z(u.z());
    init();
    return *this;
}

AreaLight &AreaLight::forward(float x, float y, float z) {
    _u.x(x);
    _u.y(y);
    _u.z(z);
    init();
    return *this;
}

AreaLight &AreaLight::length(float len) {
    _len = len;
    return *this;
}

}