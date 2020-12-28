//
// Created by dreamscached on 28.12.2020.
//

#ifndef IMDIFF_IMAGES_HPP
#define IMDIFF_IMAGES_HPP

#include "imagemagick.hpp"
#include "iostream.hpp"
#include "string.hpp"
#include "libintl.hpp"
#include "filesystem.hpp"

namespace IMD::Images {
    Magick::Image *readImage(std::filesystem::path &path);

    Magick::Image *readImage(std::string &path);

    std::string toString(Magick::Image &image);
}

#endif //IMDIFF_IMAGES_HPP
