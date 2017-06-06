#pragma once
#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

Mat bilateralFilter(const Mat & src, const double spaceSigma, const double distanceSigma);
Mat bilateralFilter(const Mat & src, const double spaceSigma, const double distanceSigma, const int grayscale);

#define GRAYSCLAE  0
#define ORIGINAL_IMAGE  "ORIGINAL IMAGE"
#define BILATERAL_IMAGE "BILATERAL IMAGE"

