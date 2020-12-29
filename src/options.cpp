//
// Created by dreamscached on 28.12.2020.
//

#include "options.hpp"

IMD::Options::Options IMD::Options::parseOptions(int argc, char **argv) {
    IMD::Options::Options options;
    CLI::App app("imdiff - image similarity score calculator");
    app.add_option("ORIGINAL", options.originalPath, "original image path")
            ->check(CLI::ExistingFile)
            ->required();
    app.add_option("PATHS", options.processPaths, "image paths to process")
            ->check(CLI::ExistingPath)
            ->required();
    app.add_flag("-r,--recurse", options.recurse, "recurse into directories");
    app.add_flag("-p,--fingerprints", options.exportFingerprints,
                 "export fingerprints in Base64 format");
    app.add_flag("-s,--score", options.printSimilarityScore, "print similarity score")
            ->default_val(options.printSimilarityScore);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        exit(app.exit(e));
    }

    return options;
}
