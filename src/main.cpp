//
// Created by dreamscached on 25.12.2020.
//

#include "imdiff.hpp"

using namespace cv;
using namespace std;
using namespace imdiff;

int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "Usage: imdiff FIRST SECOND" << endl;
        exit(0);
    }

    Mat first = imread(string(argv[1]));
    Mat second = imread(string(argv[2]));

    equalSize(first, second);
    cout << score(first, second) << endl;
}