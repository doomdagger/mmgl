#include <cmath>
#include <string>

#include "mmgl/mmgl.h"

using namespace mmgl;

int main(int argc, char* argv[]) {
    constexpr double PI {3.14159265};

    Scene scene;
    if (argc == 2) {
    	scene.config().thread_num(std::stoi(argv[1]));
    }
    scene.config().pixel_sampling_num(2)
                  .render_flag(Render::BVH);

    scene.camera().at(0, 0, 0)
                  .facing(0, 0, 1)
                  .focal_length(50)
                  .view_range(50, 50)
                  .image_size(1000, 1000);

    scene.pointLight().at(0, 0, -50).in(1, 1, 0);
    scene.ambientLight().in(0.05, 0.05, 0.05);

    auto& sphere = scene.sphere().radius(3);
    for (int i = 0; i < 8; ++i) {
        sphere.at(20 * std::sin(i*PI/4), 20 * std::cos(i*PI/4), 50);
        scene.render();
        scene.save(std::string("sphere") + std::to_string(i) + ".bmp");
    }

    return 0;
}
