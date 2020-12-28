//
// Created by dreamscached on 28.12.2020.
//

#include "options.hpp"

IMD::Options::Options IMD::Options::parseOptions(int argc, char **argv) {
    IMD::Options::Options options;
    CLI::App app("image similarity score calculator");
    app.add_option("originalPath", options.originalPath, "original image path");
    app.add_option("processPaths", options.processPaths, "image paths to process");
    app.add_flag("-r,--recurse", options.recurse, "recurse into directories");
    app.add_flag("-p,--fingerprints", options.exportFingerprints,
                 "export fingerprints in Base64 format");
    app.add_flag("-s,--score", options.printSimilarityScore,
                 "print similarity score")->default_val(options.printSimilarityScore);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        exit(app.exit(e));
    }

    return options;
}