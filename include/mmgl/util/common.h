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
#include "mmgl/util/exception.h"

namespace mmgl {

/**
 * Alias for the rendering result RGB matrix.
 */
using RenderResult = std::vector<std::vector<Vector>>;

/**
 * Render algorithm options.
 */
enum class Render {
    NORMAL = 0,         /** The Basic ray tracing algorithm */
    BBOX_ONLY = 1,      /** Bounding box only */
    BVH_BBOX_ONLY = 2,  /** BVH bounding box only*/
    BVH = 3             /** BVH structure for acceleration */
};

/**
 * BVH options.
 */
enum class BVH {
    VOLUME_CUT = 0,     /** Volume cut option for BVH tree */
    COUNT_CUT = 1       /** Count cut option for BVH tree */
};

/**
 * Multithreading method options provided.
 */;
enum class ParallelMethod {
    STD_ASYNC,          /** use std::async */
    STD_ASYNC_FORCE,    /** use std::async with std::launch::async */
    THREAD_POOL         /** use customized thread pool */
};

float get_token_as_float(std::string inString, int whichToken);

void parse_obj_file(const std::string &file, std::vector<int> &tris, std::vector<float> &verts);

// float rand_float();

}

#endif //RAYTRACER_COMMON_H
