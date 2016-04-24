//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "common.h"

// this is called from the parseSceneFile function, which uses
// it to get the float from the correspoding position on the line.
//
// return the corresponding token in the inString. Errors out
// if you've asked for more than are in the line.
//
// you really don't need to know what is going on in here, I think.
//
float get_token_as_float(std::string inString, int whichToken) {

    float thisFloatVal;    // the return value

    if (whichToken == 0) {
        std::cerr << "error: the first token on a line is a character!" << std::endl;
        exit(-1);
    }

    // c++ string class has no super-easy way to tokenize, let's use c's:
    char *cstr = new char[inString.size() + 1];

    strcpy(cstr, inString.c_str());

    char *p = strtok(cstr, " ");
    if (p == 0) {
        std::cerr << "error: the line has nothing on it!" << std::endl;
        exit(-1);
    }

    for (int i = 0; i < whichToken; i++) {
        p = strtok(0, " ");
        if (p == 0) {
            std::cerr << "error: the line is not long enough for your token request!" << std::endl;
            exit(-1);
        }
    }

    thisFloatVal = static_cast<float>(std::atof(p));

    delete[] cstr;

    return thisFloatVal;
}


void parse_obj_file(const std::string &file, std::vector<int> &tris, std::vector<float> &verts) {
    // clear out the tris and verts vectors:
    tris.clear();
    verts.clear();

    std::ifstream in(file.c_str());

    if (!in.good()) {
        std::cout << "Fails at reading file " << file << std::endl;
        return;
    }

    char buffer[1025];
    std::string cmd;

    for (int line = 1; in.good(); line++) {
        in.getline(buffer, 1024);
        buffer[in.gcount()] = 0;

        cmd = "";

        std::istringstream iss(buffer);

        iss >> cmd;

        if (cmd[0] == '#' or cmd.empty()) {
            // ignore comments or blank lines
            continue;
        }
        else if (cmd == "v") {
            // got a vertex:

            // read in the parameters:
            float pa, pb, pc;
            iss >> pa >> pb >> pc;

            verts.push_back(pa);
            verts.push_back(pb);
            verts.push_back(pc);
        }
        else if (cmd == "f") {
            // got a face (triangle)

            // read in the parameters:
            int i, j, k;
            iss >> i >> j >> k;

            // vertex numbers in OBJ files start with 1, but in C++ array
            // indices start with 0, so we're shifting everything down by
            // 1
            tris.push_back(i - 1);
            tris.push_back(j - 1);
            tris.push_back(k - 1);
        }
        else {
            std::cerr << "Parser error: invalid command at line " << line << std::endl;
        }

    }

    in.close();
}

float rand_float() {
    return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
}
