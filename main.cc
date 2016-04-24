#include <iostream>

using namespace std;

#include "scene.h"

int main() {
    Scene scene("/home/lihe/Desktop/parser/simpletestscene.txt");

    scene.render();
    return 0;
}