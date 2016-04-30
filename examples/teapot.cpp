#include <string>

#include "mmgl/mmgl.h"

using namespace mmgl;

int main(int argc, char *argv[]) {
    Scene scene("teapot.txt");

    if (argc == 2) {
    	scene.config().thread_num(std::stoi(argv[1]));
    }
    scene.config().pixel_sampling_num(1)
                  .recursive_limit(2)
                  .render_flag(Render::BVH);

    scene.render();
    scene.save("teapot.bmp");

    return 0;
}
