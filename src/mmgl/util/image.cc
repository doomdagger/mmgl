//
// Created by lihe on 4/26/16.
//

#include "mmgl/util/image.h"

namespace mmgl {

Image::Image(int width, int height) {
    resize(width, height);
}

void Image::resize(int width, int height) {
    // if size is not change, we simply clear the content
    if (width == _width && height == _height) {
        clear();
        return;
    }

    _image.empty();
    for (int i = 0; i < height; ++i) {
        std::vector<Vector> row;
        for (int j = 0; j < width; ++j) {
            row.push_back(std::move(Vector{}));
        }
        _image.push_back(std::move(row));
    }
    _width = width;
    _height = height;
}

void Image::clear() {
    for (auto &row : _image) {
        for (auto &rgb : row) {
            rgb.x(.0f);
            rgb.y(.0f);
            rgb.z(.0f);
        }
    }
}

void Image::pixel(int width, int height, const Vector &rgb) {
    _image[height][width].x(rgb.x());
    _image[height][width].y(rgb.y());
    _image[height][width].z(rgb.z());
}

const Vector &Image::pixel(int width, int height) const {
    return _image[height][width];
}

void Image::save(const std::string &file_path) const {
    FILE *f;
    unsigned char *img = nullptr;
    int filesize = 54 + 3 * _width * _height;  //w is your image width, h is image height, both int
    int x, y;
    float r, g, b;

    img = new unsigned char[3 * _width * _height];
    std::memset(img, 0, sizeof(img));

    for (int i = 0; i < _width; i++) {
        for (int j = 0; j < _height; j++) {
            const Vector &rgb = _image[j][i];
            x = i;
            y = (_height - 1) - j;
            r = rgb.x() * 255;
            g = rgb.y() * 255;
            b = rgb.z() * 255;
            if (r > 255) r = 255;
            if (g > 255) g = 255;
            if (b > 255) b = 255;
            img[(x + y * _width) * 3 + 2] = (unsigned char) (r);
            img[(x + y * _width) * 3 + 1] = (unsigned char) (g);
            img[(x + y * _width) * 3 + 0] = (unsigned char) (b);
        }
    }

    unsigned char bmpfileheader[14] = {'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0};
    unsigned char bmpinfoheader[40] = {40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0};
    unsigned char bmppad[3] = {0, 0, 0};

    bmpfileheader[2] = (unsigned char) (filesize);
    bmpfileheader[3] = (unsigned char) (filesize >> 8);
    bmpfileheader[4] = (unsigned char) (filesize >> 16);
    bmpfileheader[5] = (unsigned char) (filesize >> 24);

    bmpinfoheader[4] = (unsigned char) (_width);
    bmpinfoheader[5] = (unsigned char) (_width >> 8);
    bmpinfoheader[6] = (unsigned char) (_width >> 16);
    bmpinfoheader[7] = (unsigned char) (_width >> 24);
    bmpinfoheader[8] = (unsigned char) (_height);
    bmpinfoheader[9] = (unsigned char) (_height >> 8);
    bmpinfoheader[10] = (unsigned char) (_height >> 16);
    bmpinfoheader[11] = (unsigned char) (_height >> 24);

    f = fopen(file_path.c_str(), "wb");
    fwrite(bmpfileheader, 1, 14, f);
    fwrite(bmpinfoheader, 1, 40, f);
    for (int i = 0; i < _height; i++) {
        fwrite(img + (_width * (i) * 3), 3, _width, f);
        fwrite(bmppad, 1, (4 - (_width * 3) % 4) % 4, f);
    }
    fclose(f);
    delete [] img;
}

}