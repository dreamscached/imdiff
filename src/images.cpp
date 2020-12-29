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
        std::cerr << "Image at " << path.string() << "  is corrupt." << "\n";
    } catch (Magick::ErrorMissingDelegate &e) {
        std::cerr << "Image at " << path.string() << " is of an unknown type." << "\n";
    } catch (Magick::ErrorImage &e) {
        std::cerr << "Image at " << path.string() << "  could not be read." << "\n";
    }

    return nullptr;
}

Magick::Image *IMD::Images::readImage(std::string &path) {
    auto pathObj = std::filesystem::path(path);
    return IMD::Images::readImage(pathObj);
}
