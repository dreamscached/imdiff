//
// Created by dreamscached on 25.12.2020.
//

#ifndef IMDIFF_FINGERPRINT_HPP
#define IMDIFF_FINGERPRINT_HPP

#include "imagemagick.hpp"
#include "math.hpp"
#include "filesystem.hpp"
#include "string.hpp"

namespace IMD::Fingerprint {
    Magick::Image getFingerprint(Magick::Image &image);

    Magick::Image getFingerprint(std::filesystem::path &path);

    Magick::Image getFingerprint(std::string &path);

    double getSimilarityScore(Magick::Image &first, Magick::Image &second);
}

#endif //IMDIFF_FINGERPRINT_HPP