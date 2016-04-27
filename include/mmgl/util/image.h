//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
// Code Credit to deusmacabre (http://stackoverflow.com/users/318726/deusmacabre):
// A post from stackoverflow about how to write bmp image in pure c/c++, see the link below
// http://stackoverflow.com/questions/2654480/writing-bmp-image-in-pure-c-c-without-other-libraries
//

#ifndef MMGL_IMAGE_H
#define MMGL_IMAGE_H

#include <vector>
#include <cstring>

#include "mmgl/util/vector.h"

namespace mmgl {

class Image {
public:
    Image(): _image{} {}

    Image(int width, int height);

    inline int width() const {
        return _width;
    }

    inline int height() const {
        return _height;
    }

    void resize(int width, int height);

    void clear();

    inline std::vector<Vector> &operator[](int height) {
        return _image[height];
    }

    inline const std::vector<Vector> &operator[](int height) const {
        return _image[height];
    }

    void pixel(int width, int height, const Vector &rgb);

    const Vector &pixel(int width, int height) const;

    void save(const std::string &file_path) const;

private:
    int _width;
    int _height;
    std::vector<std::vector<Vector>> _image;
};

}


#endif //MMGL_IMAGE_H
