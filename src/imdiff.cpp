//
// Created by dreamscached on 25.12.2020.
//

#include "imdiff.hpp"

double imdiff::score(cv::Mat &first, cv::Mat &second) {
    cv::Mat scoreMat;
    double scoreDouble;

    cv::matchTemplate(first, second, scoreMat, cv::TM_CCOEFF_NORMED);
    cv::minMaxLoc(scoreMat, nullptr, &scoreDouble);

    return scoreDouble;
}

void imdiff::equalSize(cv::Mat &first, cv::Mat &second) {
    cv::Mat resized;
    if (first.cols * first.rows > second.cols * second.rows) {
        cv::resize(first, resized, cv::Size(second.cols, second.rows), 0, 0, cv::INTER_LINEAR);
        first = resized;
    } else if (first.cols * first.rows < second.cols * second.rows) {
        cv::resize(second, resized, cv::Size(first.cols, first.rows), 0, 0, cv::INTER_LINEAR);
        second = resized;
    }
}
