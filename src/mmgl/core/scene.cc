//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#include "mmgl/core/scene.h"

namespace mmgl {

Scene::Scene(const std::string &scene_file) {
    std::ifstream inFile(scene_file);    // open the file
    std::string line;

    if (!inFile.is_open()) {  // if it's not open, error out.
        throw new std::runtime_error("Scene: Cannot open scene file '" + scene_file + "'");
    }

    // Note: you'll have to keep track of whatever the last material
    // you loaded in was, so you can apply it to any geometry that gets loaded.
    // So here, you'll have something like:
    //
    // myMaterialClass *lastMaterialLoaded = 0;  // 0 or maybe a default material?
    //
    // and each time you load in a new piece of geometry (sphere, triangle, plane)
    // you will set its material to lastMaterialLoaded.

    Material lastMaterialLoaded;
    float x, y, z, x2, y2, z2, x3, y3, z3;
    float r, g, b;
    float dr, dg, db, sr, sg, sb, ir, ig, ib;
    float d, iw, ih;
    int pw, ph;
    unsigned long n;
    std::vector<int> tris;
    std::vector<float> verts;

    while (!inFile.eof()) {   // go through every line in the file until finished

        getline(inFile, line); // get the line

        switch (line[0]) {     // we'll decide which command based on the first character

            //
            // geometry types:
            //
            // NOTE: whichever type of geo you load in, set its material to
            // be "lastMaterialLoaded"
            //
            case 's':
                // it's a sphere, load in the parameters

                x = get_token_as_float(line, 1);
                y = get_token_as_float(line, 2);
                z = get_token_as_float(line, 3);
                r = get_token_as_float(line, 4);

                // build your sphere here from the parameters
                // i.e. you must call your sphere constructor and set its position
                // and radius from the above values. You must also put your new
                // sphere into the objects list (which can be global)
                // So something like;
                sphere(x, y, z, r, lastMaterialLoaded);

                break;

            case 't':   // triangle
                x = get_token_as_float(line, 1);
                y = get_token_as_float(line, 2);
                z = get_token_as_float(line, 3);
                x2 = get_token_as_float(line, 4);
                y2 = get_token_as_float(line, 5);
                z2 = get_token_as_float(line, 6);
                x3 = get_token_as_float(line, 7);
                y3 = get_token_as_float(line, 8);
                z3 = get_token_as_float(line, 9);

                triangle(x, y, z, x2, y2, z2, x3, y3, z3, lastMaterialLoaded);

                break;

                //
                // camera:
                //
            case 'c':   // camera
                // one trick here: the cameras pixel count (width, height) are integers,
                // so cast them.

                x = get_token_as_float(line, 1);
                y = get_token_as_float(line, 2);
                z = get_token_as_float(line, 3);
                x2 = get_token_as_float(line, 4);
                y2 = get_token_as_float(line, 5);
                z2 = get_token_as_float(line, 6);
                d = get_token_as_float(line, 7);
                iw = get_token_as_float(line, 8);
                ih = get_token_as_float(line, 9);
                pw = static_cast<int>(get_token_as_float(line, 10));
                ph = static_cast<int>(get_token_as_float(line, 11));

                _camera.config(x, y, z, d, x2, y2, z2, pw, ph, iw, ih);

                break;

                //
                // lights:
                //
            case 'l':   // light

                // slightly different from the rest, we need to examine the second param,
                // which is at the third position on the line:
                switch (line[2]) {
                    case 'p':   // point light
                        x = get_token_as_float(line, 2);
                        y = get_token_as_float(line, 3);
                        z = get_token_as_float(line, 4);
                        r = get_token_as_float(line, 5);
                        g = get_token_as_float(line, 6);
                        b = get_token_as_float(line, 7);

                        pointLight(x, y, z, r, g, b);

                        break;
                    case 'd':   // directional light
                        break;
                    case 'a':   // ambient light

                        r = get_token_as_float(line, 2);
                        g = get_token_as_float(line, 3);
                        b = get_token_as_float(line, 4);

                        ambientLight(r, g, b);

                        break;
                    case 's':   // square area light
                        x = get_token_as_float(line, 2);
                        y = get_token_as_float(line, 3);
                        z = get_token_as_float(line, 4);
                        x2 = get_token_as_float(line, 5);
                        y2 = get_token_as_float(line, 6);
                        z2 = get_token_as_float(line, 7);
                        x3 = get_token_as_float(line, 8);
                        y3 = get_token_as_float(line, 9);
                        z3 = get_token_as_float(line, 10);
                        d = get_token_as_float(line, 11);
                        r = get_token_as_float(line, 12);
                        g = get_token_as_float(line, 13);
                        b = get_token_as_float(line, 14);

                        areaLight(x, y, z, x2, y2, z2, x3, y3, z3, d, r, g, b);

                        break;
                    default:
                        throw std::runtime_error("Unknown symbols for light in scene file");

                }

                break;

                //
                // materials:
                //
            case 'm':   // material
                // the trick here: we should keep a pointer to the last material we read in,
                // so we can apply it to any subsequent geometry. Say it's called "lastMaterialLoaded"
                // we migh then do something like this:
                //
                //  1. read in the 10 material parameters: dr, dg, db, sr, sg, sb, r, ir, ig, ib
                //  2. call lastMaterialLoaded->setMaterial(dr, dg, db,...);
                //

                dr = get_token_as_float(line, 1);
                dg = get_token_as_float(line, 2);
                db = get_token_as_float(line, 3);
                sr = get_token_as_float(line, 4);
                sg = get_token_as_float(line, 5);
                sb = get_token_as_float(line, 6);
                r = get_token_as_float(line, 7);
                ir = get_token_as_float(line, 8);
                ig = get_token_as_float(line, 9);
                ib = get_token_as_float(line, 10);

                lastMaterialLoaded = Material{dr, dg, db, sr, sg, sb, ir, ig, ib, r};

                break;

            case 'w':
                parse_obj_file(line.substr(line.find(' ') + 1), tris, verts);

                n = tris.size() / 3;
                for (unsigned long i = 0; i < n; ++i) {
                    x = verts[3 * tris[3 * i]];
                    y = verts[3 * tris[3 * i] + 1];
                    z = verts[3 * tris[3 * i] + 2];
                    x2 = verts[3 * tris[3 * i + 1]];
                    y2 = verts[3 * tris[3 * i + 1] + 1];
                    z2 = verts[3 * tris[3 * i + 1] + 2];
                    x3 = verts[3 * tris[3 * i + 2]];
                    y3 = verts[3 * tris[3 * i + 2] + 1];
                    z3 = verts[3 * tris[3 * i + 2] + 2];
                    triangle(x, y, z, x2, y2, z2, x3, y3, z3, lastMaterialLoaded);
                }

                break;

            case '/':
                // don't do anything, it's a comment
                break;


                //
                // options
                //
            case 'o':   // make your own options if you wish
                break;

            default:
                break;
        }

    }
}

void Scene::render() {
    if (_surfaces.empty()) {
        std::cerr << "Please at least pass in one surface to render, or do you really want a fully-dark image?" << std::endl;
        return;
    }

    std::vector<Surface *> objects_vec;
    std::vector<Light *> lights_vec;

    std::copy(_surfaces.begin(), _surfaces.end(), std::back_inserter(objects_vec));
    std::copy(_lights.begin(), _lights.end(), std::back_inserter(lights_vec));

    // build bvh tree
    BVHNode *parent = nullptr;
    if (_config.render_flag() == Render::BVH || _config.render_flag() == Render::BVH_BBOX_ONLY) {
        // in case of we only have one object
        if (!(parent = dynamic_cast<BVHNode *>(
                BVHNode::create_bvh_tree(objects_vec.begin(), objects_vec.end(), _config.bvh_mode())))) {
            parent = new BVHNode(objects_vec.begin(), objects_vec.end());
            parent->_left = objects_vec[0];
        }
    }

    // render
    std::cerr << "Start to render..." << std::endl;
    using namespace std::chrono;
    auto func_start = high_resolution_clock::now();
    _camera.render(objects_vec, lights_vec, parent, _config);
    auto func_end = high_resolution_clock::now();
    std::cerr << "Finish rendering in " << duration_cast<milliseconds>(func_end - func_start).count() << " ms" << std::endl;

    // clean up memory, using BFS
    if (parent) {
        std::queue<BVHNode *> q;
        q.push(parent);
        while (!q.empty()) {
            BVHNode *node = q.front();
            q.pop();

            BVHNode *node_left = nullptr;
            BVHNode *node_right = nullptr;

            if (node->_left && (node_left = dynamic_cast<BVHNode *>(node->_left))) {
                q.push(node_left);
            }
            if (node->_right && (node_right = dynamic_cast<BVHNode *>(node->_right))) {
                q.push(node_right);
            }

            delete node;
        }
    }
}

Sphere &Scene::sphere(float x, float y, float z, float radius, const Material &material) {
    Sphere *surface = new Sphere(x, y, z, radius);
    surface->material(material);
    _surfaces.push_back(surface);
    return *surface;
}

Triangle &Scene::triangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3,
                          float z3, const Material &material) {
    Triangle *surface = new Triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
    surface->material(material);
    _surfaces.push_back(surface);
    return *surface;
}

PointLight &Scene::pointLight(float x, float y, float z, float r, float g, float b) {
    PointLight *light = new PointLight(x, y, z, r, g, b);
    _lights.push_back(light);
    return *light;
}

AreaLight &Scene::areaLight(float x, float y, float z, float nx, float ny, float nz, float ux, float uy, float uz,
                            float len, float r, float g, float b) {
    AreaLight *light = new AreaLight{x, y, z, nx, ny, nz, ux, uy, uz, len, r, g, b};
    _lights.push_back(light);
    return *light;
}

AmbientLight &Scene::ambientLight(float r, float g, float b) {
    AmbientLight *light = new AmbientLight{r, g, b};
    _lights.push_back(light);
    return *light;
}

Scene::~Scene() {
    for (auto &elem : _surfaces) {
        delete elem;
    }

    for (auto &elem : _lights) {
        delete elem;
    }
}

void Scene::configCamera(float x, float y, float z, float dx, float dy, float dz, float d,
                         float iw, float ih, int nx, int ny) {
    _camera.config(x, y, z, d, dx, dy, dz, nx, ny, iw, ih);
}

void Scene::save(const std::string &file_path) const {
    _camera.writeRgba(file_path);
}

}