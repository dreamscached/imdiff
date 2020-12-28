//
// Created by dreamscached on 25.12.2020.
//

#include "fingerprint.hpp"

Magick::Image IMD::Fingerprint::getFingerprint(Magick::Image &image) {
    // Turn image grayscale and shrink it to 8x8.
    Magick::Image fingerprint(image);
    fingerprint.type(Magick::GrayscaleType);
    fingerprint.resize(Magick::Geometry(8, 8));

    return fingerprint;
}

double IMD::Fingerprint::getSimilarityScore(Magick::Image &first, Magick::Image &second) {
    Magick::Pixels firstPixels(first);
    Magick::Pixels secondPixels(second);

    double values[64];
    for (auto j = 0; j < 8; j++) {
        auto firstRow = firstPixels.getConst(0, j, 8, 1);
        auto secondRow = secondPixels.getConst(0, j, 8, 1);

        for (auto i = 0; i < 8; i++) {
            // Since fingerprint image is grayscale, there's no need to fetch other channels.
            // For instance, here we implicitly use R (pointer offset +0.)
            double firstValue = 255 * QuantumScale * *firstRow++;
            double secondValue = 255 * QuantumScale * *secondRow++;

            // We need to get double in range [0; 1], thus we need to divide lesser by greater.
            values[8 * j + i] = IMD::Math::min(firstValue, secondValue) / IMD::Math::max(firstValue, secondValue);
        }
    }

    return IMD::Math::mean(64, values);
}
