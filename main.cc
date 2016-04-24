#include <iostream>

using namespace std;

#include "scene.h"

int main() {
    Scene scene;

    scene.NewSphere(0, 13.67f, -62.57f, 10);

    scene.NewPointLight(-80, 120, -46.6f, 1, 1, 1);
    scene.NewAmbientLight(0.05, 0.05, 0.05);

    scene.ConfigCamera(24.2, 29.3, 53.6, 35, 0, 0, -1, 1000, 1000, 35, 35);

    scene.render();

    scene.save("/home/lihe/Desktop/test.exr");

    scene.ConfigCamera(24.2, 29.3, 33.6, 35, 0, 0, -1, 1000, 1000, 35, 35);

    scene.render();

    scene.save("/home/lihe/Desktop/test1.exr");

    return 0;
}