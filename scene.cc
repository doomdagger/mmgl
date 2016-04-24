//
// Created by lihe on 4/22/16.
//

#include "scene.h"

Scene::Scene(const std::string &scene_file) {
    std::ifstream inFile(scene_file);    // open the file
    std::string line;

    if (!inFile.is_open()) {  // if it's not open, error out.
        std::cerr << "can't open scene file" << std::endl;
        exit(-1);
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

                x = getTokenAsFloat(line, 1);
                y = getTokenAsFloat(line, 2);
                z = getTokenAsFloat(line, 3);
                r = getTokenAsFloat(line, 4);

                // build your sphere here from the parameters
                // i.e. you must call your sphere constructor and set its position
                // and radius from the above values. You must also put your new
                // sphere into the objects list (which can be global)
                // So something like;
                {
                    NewSphere(x, y, z, r, lastMaterialLoaded);
                }

#ifdef IM_DEBUGGING
            // if we're debugging, show what we got:
                cout << "got a sphere with ";
                cout << "parameters: " << x << " " << y << " " << z << " " << r << endl;
#endif
                break;

            case 't':   // triangle
                x = getTokenAsFloat(line, 1);
                y = getTokenAsFloat(line, 2);
                z = getTokenAsFloat(line, 3);
                x2 = getTokenAsFloat(line, 4);
                y2 = getTokenAsFloat(line, 5);
                z2 = getTokenAsFloat(line, 6);
                x3 = getTokenAsFloat(line, 7);
                y3 = getTokenAsFloat(line, 8);
                z3 = getTokenAsFloat(line, 9);

                {
                    NewTriangle(x, y, z, x2, y2, z2, x3, y3, z3, lastMaterialLoaded);
                }

                break;

//            case 'p':   // plane
//                x = getTokenAsFloat(line, 1);
//                y = getTokenAsFloat(line, 2);
//                z = getTokenAsFloat(line, 3);
//                d = getTokenAsFloat(line, 4);
//
//                {
//                    Plane *plane = new Plane{x, y, z, d};
//                    plane->material(lastMaterialLoaded);
//                    objects.push_back(plane);
//                }
//
//                break;

                //
                // camera:
                //
            case 'c':   // camera
                // one trick here: the cameras pixel count (width, height) are integers,
                // so cast them.

                x = getTokenAsFloat(line, 1);
                y = getTokenAsFloat(line, 2);
                z = getTokenAsFloat(line, 3);
                x2 = getTokenAsFloat(line, 4);
                y2 = getTokenAsFloat(line, 5);
                z2 = getTokenAsFloat(line, 6);
                d = getTokenAsFloat(line, 7);
                iw = getTokenAsFloat(line, 8);
                ih = getTokenAsFloat(line, 9);
                pw = static_cast<int>(getTokenAsFloat(line, 10));
                ph = static_cast<int>(getTokenAsFloat(line, 11));

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
                        x = getTokenAsFloat(line, 2);
                        y = getTokenAsFloat(line, 3);
                        z = getTokenAsFloat(line, 4);
                        r = getTokenAsFloat(line, 5);
                        g = getTokenAsFloat(line, 6);
                        b = getTokenAsFloat(line, 7);

                        {
                            NewPointLight(x, y, z, r, g, b);
                        }

                        break;
                    case 'd':   // directional light
                        break;
                    case 'a':   // ambient light

                        r = getTokenAsFloat(line, 2);
                        g = getTokenAsFloat(line, 3);
                        b = getTokenAsFloat(line, 4);

                        {
                            NewAmbientLight(r, g, b);
                        }

                        break;
                    case 's':   // square area light
                        x = getTokenAsFloat(line, 2);
                        y = getTokenAsFloat(line, 3);
                        z = getTokenAsFloat(line, 4);
                        x2 = getTokenAsFloat(line, 5);
                        y2 = getTokenAsFloat(line, 6);
                        z2 = getTokenAsFloat(line, 7);
                        x3 = getTokenAsFloat(line, 8);
                        y3 = getTokenAsFloat(line, 9);
                        z3 = getTokenAsFloat(line, 10);
                        d = getTokenAsFloat(line, 11);
                        r = getTokenAsFloat(line, 12);
                        g = getTokenAsFloat(line, 13);
                        b = getTokenAsFloat(line, 14);

                        {
                            NewAreaLight(x, y, z, x2, y2, z2, x3, y3, z3, d, r, g, b);
                        }

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

                dr = getTokenAsFloat(line, 1);
                dg = getTokenAsFloat(line, 2);
                db = getTokenAsFloat(line, 3);
                sr = getTokenAsFloat(line, 4);
                sg = getTokenAsFloat(line, 5);
                sb = getTokenAsFloat(line, 6);
                r = getTokenAsFloat(line, 7);
                ir = getTokenAsFloat(line, 8);
                ig = getTokenAsFloat(line, 9);
                ib = getTokenAsFloat(line, 10);

                lastMaterialLoaded = Material{dr, dg, db, sr, sg, sb, ir, ig, ib, r};

                break;

            case 'w':
                parseObjFile(line.substr(line.find(' ') + 1), tris, verts);

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
                    NewTriangle(x, y, z, x2, y2, z2, x3, y3, z3, lastMaterialLoaded);
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
        std::cerr << "Please at least pass in one surface to render, or do you really want a fully-dark image?" <<
        std::endl;
    }

    std::vector<Surface *> objects_vec = surfaces();
    std::vector<Light *> lights_vec = lights();

    // in case we only have one surface
    BVHNode *parent = nullptr;
    // in case of we only have one object
    if (!(parent = dynamic_cast<BVHNode *>(BVHNode::create_bvh_tree(objects_vec.begin(), objects_vec.end())))) {
        parent = new BVHNode(objects_vec.begin(), objects_vec.end());
        parent->_left = objects_vec[0];
    }

    _camera.render(objects_vec, lights_vec, parent, config);
    _camera.writeRgba("/home/lihe/Desktop/test.exr");

    // clean up memory, using BFS
    std::queue<Surface *> q;
    q.push(parent);
    while (!q.empty()) {
        Surface *temp = q.front();
        q.pop();
        if (BVHNode *node = dynamic_cast<BVHNode *>(temp)) {
            if (node->_left) {
                q.push(node->_left);
            }
            if (node->_right) {
                q.push(node->_right);
            }
            // only delete bvh node
            delete temp;
        }
    }
}

unsigned long Scene::NewSphere(float x, float y, float z, float radius, const Material &material) {
    Surface *surface = new Sphere(x, y, z, radius);
    surface->material(material);
    _surfaces[++_surface_id] = surface;
    return _surface_id;
}

unsigned long Scene::NewTriangle(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3,
                                 float z3, const Material &material) {
    Surface *surface = new Triangle(x1, y1, z1, x2, y2, z2, x3, y3, z3);
    surface->material(material);
    _surfaces[++_surface_id] = surface;
    return _surface_id;
}

unsigned long Scene::NewPointLight(float x, float y, float z, float r, float g, float b) {
    Light *light = new PointLight(x, y, z, r, g, b);
    _lights[++_light_id] = light;
    return _light_id;
}

unsigned long Scene::NewAreaLight(float x, float y, float z, float nx, float ny, float nz, float ux, float uy, float uz,
                                  float len, float r, float g, float b) {
    Light *light = new AreaLight{x, y, z, nx, ny, nz, ux, uy, uz, len, r, g, b};
    _lights[++_light_id] = light;
    return _light_id;
}

unsigned long Scene::NewAmbientLight(float r, float g, float b) {
    Light *light = new AmbientLight{r, g, b};
    _lights[++_light_id] = light;
    return _light_id;
}
