//
// Created by dreamscached on 25.12.2020.
//

#ifndef IMDIFF_IMDIFF_HPP
#define IMDIFF_IMDIFF_HPP

#include "opencv.hpp"
#include "iostream.hpp"
#include "string.hpp"

namespace imdiff {
    void equalSize(cv::Mat &first, cv::Mat &second);

    double score(cv::Mat &first, cv::Mat &second);
}

#endif //IMDIFF_IMDIFF_HPP
