#include <iostream>
#include <string>

#include "mmgl/mmgl.h"

using namespace std;
using namespace mmgl;

int main(int argc, char *argv[]) {
    Scene scene("teapot.txt");

    if (argc == 2) {
    	scene.config.thread_num(stoi(argv[1]));
    }
    // scene.config.pixel_sampling_num(2);
    // scene.config.render_flag(Render::BVH);
    scene.config.shadow_sampling_num(1);
    scene.config.pixel_sampling_num(1);
    scene.config.recursive_limit(2);
    scene.config.render_flag(Render::BVH);

    scene.render();

    scene.save("teapot.bmp");

    return 0;
}
