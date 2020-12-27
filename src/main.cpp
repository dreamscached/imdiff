//
// Created by dreamscached on 25.12.2020.
//

#include <CLI/CLI.hpp>
#include "string.hpp"
#include "vector.hpp"

int main(int argc, char **argv) {
    CLI::App app("image difference score calculator");

    std::string originalPath;
    app.add_option("originalPath", originalPath, "original image path");

    std::vector<std::string> comparePaths;
    app.add_option("comparePaths", comparePaths, "image paths to compare");

    bool recurse;
    app.add_option("-r,--recurse", recurse, "recurse into directories");

    CLI11_PARSE(app, argc, argv)
}