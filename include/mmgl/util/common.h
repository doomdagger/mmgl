//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef RAYTRACER_COMMON_H
#define RAYTRACER_COMMON_H

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>

#include "mmgl/util/vector.h"

namespace mmgl {

using RenderResult = std::vector<std::vector<Vector>>;

enum class Render {
    NORMAL = 0,
    BBOX_ONLY = 1,
    BVH_BBOX_ONLY = 2,
    BVH = 3
};

enum class BVH {
    VOLUME_CUT = 0,
    COUNT_CUT = 1
};

enum class ParallelMethod {
    STD_ASYNC,
    STD_ASYNC_FORCE,
    THREAD_POOL
};

float get_token_as_float(std::string inString, int whichToken);

void parse_obj_file(const std::string &file, std::vector<int> &tris, std::vector<float> &verts);

// float rand_float();

}

#endif //RAYTRACER_COMMON_H
