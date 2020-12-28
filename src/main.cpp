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

    auto originalFingerprint = IMD::Fingerprint::getFingerprint(options.originalPath);

    for (auto &argumentPath : options.processPaths) {
        if (std::filesystem::is_directory(argumentPath)) {
            if (options.recurse) {
                for (auto &entry : std::filesystem::recursive_directory_iterator(argumentPath)) {
                    auto path = entry.path();
                    if (entry.is_directory() || path == options.originalPath) {
                        continue;
                    }

                    std::cout << path;
                    try {
                        auto fingerprint = IMD::Fingerprint::getFingerprint(path);
                        if (options.exportFingerprints) {
                            std::cout << "\t" << IMD::Images::toString(fingerprint);
                        }
                        if (options.printSimilarityScore) {
                            std::cout << "\t" << IMD::Fingerprint::getSimilarityScore(originalFingerprint, fingerprint);
                        }
                    } catch (Magick::ErrorCorruptImage &e) {
                        if (options.exportFingerprints) {
                            std::cout << "\t-" << std::endl;
                        }
                        if (options.printSimilarityScore) {
                            std::cout << "\t-" << std::endl;
                        }
                        std::cerr << "Skipping corrupt image " << path << "." << std::endl;
                    } catch (Magick::ErrorMissingDelegate &e) {
                        if (options.exportFingerprints) {
                            std::cout << "\t-" << std::endl;
                        }
                        if (options.printSimilarityScore) {
                            std::cout << "\t-" << std::endl;
                        }
                        std::cerr << "Skipping image of unknown type " << argumentPath << "." << std::endl;
                    } catch (Magick::ErrorImage &e) {
                        if (options.exportFingerprints) {
                            std::cout << "\t-" << std::endl;
                        }
                        if (options.printSimilarityScore) {
                            std::cout << "\t-" << std::endl;
                        }
                        std::cerr << "Skipping bad image " << argumentPath << "." << std::endl;
                    }
                    std::cout << std::endl;
                }
            } else {
                std::cerr << "Skipping directory " << argumentPath << "." << std::endl;
            }
        } else {
            if (argumentPath == options.originalPath) {
                continue;
            }

            auto fingerprint = IMD::Fingerprint::getFingerprint(argumentPath);
            try {
                std::cout << argumentPath;
                if (options.exportFingerprints) {
                    std::cout << "\t" << IMD::Images::toString(fingerprint);
                }
                if (options.printSimilarityScore) {
                    std::cout << "\t" << IMD::Fingerprint::getSimilarityScore(originalFingerprint, fingerprint);
                }
            } catch (Magick::ErrorCorruptImage &e) {
                if (options.exportFingerprints) {
                    std::cout << "\t-" << std::endl;
                }
                if (options.printSimilarityScore) {
                    std::cout << "\t-" << std::endl;
                }
                std::cerr << "Skipping corrupt image " << argumentPath << "." << std::endl;
            } catch (Magick::ErrorMissingDelegate &e) {
                if (options.exportFingerprints) {
                    std::cout << "\t-" << std::endl;
                }
                if (options.printSimilarityScore) {
                    std::cout << "\t-" << std::endl;
                }
                std::cerr << "Skipping image of unknown type " << argumentPath << "." << std::endl;
            } catch (Magick::ErrorImage &e) {
                if (options.exportFingerprints) {
                    std::cout << "\t-" << std::endl;
                }
                if (options.printSimilarityScore) {
                    std::cout << "\t-" << std::endl;
                }
                std::cerr << "Skipping bad image " << argumentPath << "." << std::endl;
            }
            std::cout << std::endl;
        }
    }
}