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

enum class Render {
    NORMAL = 0,
    BBOX_ONLY = 1,
    BVH_BBOX_ONLY = 2,
    BVH = 3
};

float getTokenAsFloat(std::string inString, int whichToken);

void parseObjFile(const std::string &file, std::vector<int> &tris, std::vector<float> &verts);


#endif //RAYTRACER_COMMON_H
