//
// Created by dreamscached on 28.12.2020.
//

#include "images.hpp"

std::string IMD::Images::toString(Magick::Image &image) {
    Magick::Blob blob;
    image.write(&blob);
    return blob.base64();
}
