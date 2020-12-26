//
// Created by dreamscached on 25.12.2020.
//

#ifndef IMDIFF_FINGERPRINT_HPP
#define IMDIFF_FINGERPRINT_HPP

#include "imagemagick.hpp"
#include "math.hpp"
#include "string.hpp"

namespace IMD::Fingerprint {
    Magick::Image fingerprint(Magick::Image &image);

    double score(Magick::Image &first, Magick::Image &second);

    std::string toString(Magick::Image &fingerprint);
}

#endif //IMDIFF_FINGERPRINT_HPP