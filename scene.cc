//
// Created by lihe on 4/22/16.
//

#include "scene.h"

Scene::Scene(const std::string &scene_file) {

}

void Scene::render() {
    if (_surfaces.empty()) {
        std::cerr << "Please at least pass in one surface to render, or do you really want a fully-dark image?" <<
        std::endl;
    }

    std::vector<Surface *> objects = surfaces();
    std::vector<Light *> lights = lights();

    // in case we only have one surface
    BVHNode *parent = nullptr;
    // in case of we only have one object
    if (!(parent = dynamic_cast<BVHNode *>(BVHNode::create_bvh_tree(objects.begin(), objects.end())))) {
        parent = new BVHNode(objects.begin(), objects.end());
        parent->_left = objects[0];
    }

    _camera.render(objects, lights, parent, config);
    _camera.writeRgba("test.exr");

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
