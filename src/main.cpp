//
// Created by dreamscached on 25.12.2020.
//

#include "cli11.hpp"
#include "string.hpp"
#include "vector.hpp"
#include "filesystem.hpp"
#include "fingerprint.hpp"
#include "images.hpp"

int main(int argc, char **argv) {
    CLI::App app("image similarity score calculator");

    std::string originalPath;
    app.add_option("originalPath", originalPath, "original image path");

    std::vector<std::string> processPaths;
    app.add_option("processPaths", processPaths, "image paths to process");

    bool recurse = false;
    app.add_flag("-r,--recurse", recurse, "recurse into directories");

    bool exportFingerprints = false;
    app.add_flag("-p,--fingerprints", exportFingerprints,
                 "export fingerprints in Base64 format");

    bool printScore = false;
    app.add_flag("-s,--score", printScore,
                 "print similarity score")->default_val(true);

    CLI11_PARSE(app, argc, argv)

    auto originalFingerprint = IMD::Fingerprint::getFingerprint(originalPath);

    for (auto &argumentPath : processPaths) {
        if (std::filesystem::is_directory(argumentPath)) {
            if (recurse) {
                for (auto &entry : std::filesystem::recursive_directory_iterator(argumentPath)) {
                    auto path = entry.path();
                    if (entry.is_directory() || path == originalPath) {
                        continue;
                    }

                    std::cout << path;
                    try {
                        auto fingerprint = IMD::Fingerprint::getFingerprint(path);
                        if (exportFingerprints) {
                            std::cout << "\t" << IMD::Images::toString(fingerprint);
                        }
                        if (printScore) {
                            std::cout << "\t" << IMD::Fingerprint::getSimilarityScore(originalFingerprint, fingerprint);
                        }
                    } catch (Magick::ErrorCorruptImage &e) {
                        if (exportFingerprints) {
                            std::cout << "\t-" << std::endl;
                        }
                        if (printScore) {
                            std::cout << "\t-" << std::endl;
                        }
                        std::cerr << "Skipping corrupt image " << path << "." << std::endl;
                    } catch (Magick::ErrorMissingDelegate &e) {
                        if (exportFingerprints) {
                            std::cout << "\t-" << std::endl;
                        }
                        if (printScore) {
                            std::cout << "\t-" << std::endl;
                        }
                        std::cerr << "Skipping image of unknown type " << argumentPath << "." << std::endl;
                    } catch (Magick::ErrorImage &e) {
                        if (exportFingerprints) {
                            std::cout << "\t-" << std::endl;
                        }
                        if (printScore) {
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
            if (argumentPath == originalPath) {
                continue;
            }

            auto fingerprint = IMD::Fingerprint::getFingerprint(argumentPath);
            try {
                std::cout << argumentPath;
                if (exportFingerprints) {
                    std::cout << "\t" << IMD::Images::toString(fingerprint);
                }
                if (printScore) {
                    std::cout << "\t" << IMD::Fingerprint::getSimilarityScore(originalFingerprint, fingerprint);
                }
            } catch (Magick::ErrorCorruptImage &e) {
                if (exportFingerprints) {
                    std::cout << "\t-" << std::endl;
                }
                if (printScore) {
                    std::cout << "\t-" << std::endl;
                }
                std::cerr << "Skipping corrupt image " << argumentPath << "." << std::endl;
            } catch (Magick::ErrorMissingDelegate &e) {
                if (exportFingerprints) {
                    std::cout << "\t-" << std::endl;
                }
                if (printScore) {
                    std::cout << "\t-" << std::endl;
                }
                std::cerr << "Skipping image of unknown type " << argumentPath << "." << std::endl;
            } catch (Magick::ErrorImage &e) {
                if (exportFingerprints) {
                    std::cout << "\t-" << std::endl;
                }
                if (printScore) {
                    std::cout << "\t-" << std::endl;
                }
                std::cerr << "Skipping bad image " << argumentPath << "." << std::endl;
            }
            std::cout << std::endl;
        }
    }
}