//
// Created by dreamscached on 25.12.2020.
//

#include "options.hpp"
#include "string.hpp"
#include "filesystem.hpp"
#include "fingerprint.hpp"
#include "images.hpp"

int main(int argc, char **argv) {
    auto options = IMD::Options::parseOptions(argc, argv);

    if (!options.noHeader) {
        std::cout << "PATH";

        if (options.printSimilarityScore) {
            std::cout << "\t" << "SCORE";
        }

        if (options.exportFingerprints) {
            std::cout << "\t" << "FINGERPRINT";
        }

        std::cout << "\n";
    }

    auto originalImage = IMD::Images::readImage(options.originalPath);
    if (originalImage != nullptr) {
        auto originalFingerprint = IMD::Fingerprint::getFingerprint(*originalImage);

        for (auto &argumentPath : options.processPaths) {
            if (argumentPath == options.originalPath) {
                continue;
            }

            if (std::filesystem::is_directory(argumentPath)) {
                if (options.recurse) {
                    for (auto &entry : std::filesystem::recursive_directory_iterator(argumentPath)) {
                        auto path = entry.path();

                        if (entry.is_directory() || entry.path() == options.originalPath) {
                            continue;
                        }

                        auto image = IMD::Images::readImage(path);
                        if (image != nullptr) {
                            auto fingerprint = IMD::Fingerprint::getFingerprint(*image);

                            std::cout << path.string();

                            if (options.printSimilarityScore) {
                                auto score = IMD::Fingerprint::getSimilarityScore(originalFingerprint, fingerprint);
                                if (options.humanReadable) {
                                    std::cout << "\t";
                                    std::fprintf(stdout, "%6.2f%%", score * 100);
                                } else {
                                    std::cout << "\t" << score;
                                }
                            }

                            if (options.exportFingerprints) {
                                auto base64 = IMD::Images::toString(fingerprint);
                                std::cout << "\t" << base64;
                            }

                            std::cout << "\n";
                            delete image;
                        }
                    }
                } else {
                    std::cerr << printf("Skipping directory %s.", argumentPath.c_str()) << "\n";
                }
            } else {
                auto image = IMD::Images::readImage(argumentPath);
                if (image != nullptr) {
                    auto fingerprint = IMD::Fingerprint::getFingerprint(*image);

                    std::cout << argumentPath;

                    if (options.printSimilarityScore) {
                        auto score = IMD::Fingerprint::getSimilarityScore(originalFingerprint, fingerprint);
                        std::cout << "\t" << score;
                    }

                    if (options.exportFingerprints) {
                        auto base64 = IMD::Images::toString(fingerprint);
                        std::cout << "\t" << base64;
                    }

                    std::cout << "\n";
                    delete image;
                }
            }
        }

        delete originalImage;
    }

    exit(0);
}