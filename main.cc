#include <iostream>

using namespace std;

#include "scene.h"

int main() {
    Scene scene;

    scene.config.pixel_sampling_num(2);
    scene.config.render_flag(Render::BVH);

//    scene.sphere(0, 13.67f, -62.57f, 10);

    Sphere &sphere = scene.sphere().at(0, 13.67f, -62.57f).radius(10);

    scene.pointLight(-80, 120, -46.6f, 1, 1, 1);
    scene.ambientLight(0.05, 0.05, 0.05);

    scene.configCamera(24.2, 29.3, 53.6, 0, 0, -1, 35, 35, 35, 1000, 1000);

    scene.render();

    scene.save("/home/lihe/Desktop/test.exr");

    sphere.at(20, 13.67f, -62.57f);

    scene.render();

    scene.save("/home/lihe/Desktop/test1.exr");

//    Scene scene("/home/lihe/Desktop/parser/chess.txt");
//
//    scene.config.shadow_sampling_num(2);
//    scene.config.pixel_sampling_num(2);
//    scene.config.recursive_limit(2);
//    scene.config.render_flag(Render::BVH);
//
//    scene.render();
//
//    scene.save("/home/lihe/Desktop/test.exr");

    return 0;
}