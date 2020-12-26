//
// Created by dreamscached on 25.12.2020.
//

#include "fingerprint.hpp"

Magick::Image IMD::Fingerprint::fingerprint(Magick::Image &image) {
    Magick::Image fingerprint(image);
    fingerprint.type(Magick::GrayscaleType);
    fingerprint.resize(Magick::Geometry(8, 8));
    return fingerprint;
}

double IMD::Fingerprint::score(Magick::Image &first, Magick::Image &second) {
    Magick::Pixels firstPixels(first);
    Magick::Pixels secondPixels(second);

    double values[64];
    for (auto j = 0; j < 8; j++) {
        auto firstRow = firstPixels.getConst(0, j, 8, 1);
        auto secondRow = secondPixels.getConst(0, j, 8, 1);
        for (auto i = 0; i < 8; i++) {
            double firstValue = 255 * QuantumScale * *firstRow++;
            double secondValue = 255 * QuantumScale * *secondRow++;

            if (IMD::Math::min(firstValue, secondValue) == firstValue) {
                values[8 * j + i] = firstValue / secondValue;
            } else {
                values[8 * j + i] = secondValue / firstValue;
            }
        }
    }

    return IMD::Math::mean(64, values);
}

std::string IMD::Fingerprint::toString(Magick::Image &fingerprint) {
    Magick::Blob blob;
    fingerprint.write(&blob);
    return blob.base64();
}