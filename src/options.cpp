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
    app.add_flag("-n,--no-header", options.printHeader, "do not print table header")
            ->default_val(options.printHeader);
    app.add_flag("-H,--human-readable", options.humanReadable, "print score in human-readable format")
            ->default_val(options.humanReadable);

    app.callback([&] {
        if (app.count("-s")) {
            options.printSimilarityScore = false;
        }

        if (app.count("-p")) {
            options.exportFingerprints = true;
        }

        if (app.count("-n")) {
            options.printHeader = false;
        }

        if (app.count("-H")) {
            options.humanReadable = true;
        }
    });

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {
        exit(app.exit(e));
    }

    return options;
}
