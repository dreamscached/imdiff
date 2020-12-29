//
// Created by dreamscached on 28.12.2020.
//

#include "images.hpp"

std::string IMD::Images::toString(Magick::Image &image) {
    Magick::Blob blob;
    image.write(&blob);
    return blob.base64();
}

Magick::Image *IMD::Images::readImage(std::filesystem::path &path) {
    try {
        return new Magick::Image(path);
    } catch (Magick::ErrorCorruptImage &e) {
        std::cerr << printf("Image at %s is corrupt.", path.c_str()) << std::endl;
    } catch (Magick::ErrorMissingDelegate &e) {
        std::cerr << printf("Image at %s is of an unknown.", path.c_str()) << std::endl;
    } catch (Magick::ErrorImage &e) {
        std::cerr << printf("Image at %s could not be read.", path.c_str()) << std::endl;
    }

    return nullptr;
}

Magick::Image *IMD::Images::readImage(std::string &path) {
    auto pathObj = std::filesystem::path(path);
    return IMD::Images::readImage(pathObj);
}
