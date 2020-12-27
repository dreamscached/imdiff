//
// Created by dreamscached on 25.12.2020.
//

#include "math.hpp"

double IMD::Math::mean(int count, const double *values) {
    double sum = 0;
    for (auto i = 0; i < count; i++) {
        sum += values[i];
    }
    return sum / (double) count;
}

double IMD::Math::min(double first, double second) {
    return first > second ? second : first;
}

double IMD::Math::max(double first, double second) {
    return first < second ? second : first;
}
