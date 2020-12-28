//
// Created by dreamscached on 28.12.2020.
//

#ifndef IMDIFF_OPTIONS_HPP
#define IMDIFF_OPTIONS_HPP

#include "cli11.hpp"
#include "libintl.hpp"

namespace IMD::Options {
    struct Options {
        std::string originalPath;
        std::vector<std::string> processPaths;
        bool recurse{false};
        bool exportFingerprints{false};
        bool printSimilarityScore{true};
    };

    Options parseOptions(int argc, char **argv);
}

#endif //IMDIFF_OPTIONS_HPP
