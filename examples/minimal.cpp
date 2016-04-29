#include "mmgl/mmgl.h"

using namespace mmgl;

int main() {
    Scene scene;
    scene.pointLight();
    scene.sphere();
    scene.render();
    scene.save("minimal.bmp");
    return 0;
}
