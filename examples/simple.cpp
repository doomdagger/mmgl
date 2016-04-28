#include <iostream>
#include <string>

#include "mmgl/mmgl.h"

using namespace std;
using namespace mmgl;

int main(int argc, char *argv[]) {
    Scene scene;

    if (argc == 2) {
    	scene.config.thread_num(stoi(argv[1]));
    }
    scene.config.pixel_sampling_num(2);
    scene.config.render_flag(Render::BVH);
    scene.configCamera(24.2, 29.3, 53.6, 0, 0, -1, 35, 35, 35, 1000, 1000);

    // Sphere &sphere = scene.sphere().at(0, 13.67f, -62.57f).radius(10);
    // scene.pointLight(-80, 120, -46.6f, 1, 1, 1);
    // scene.ambientLight(0.05, 0.05, 0.05);

    scene.add(Sphere().at(0, 13.67f, -62.57f).radius(10))
         .add(PointLight().at(-80, 120, -46.6f).in(1, 1, 1))
	     .add(AmbientLight().in(0.05, 0.05, 0.05));

    scene.render();

    scene.save("simple.bmp");

    //sphere.at(20, 13.67f, -62.57f);
    //scene.render();
    //scene.save("simple2.bmp");

    return 0;
}
