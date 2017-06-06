#pragma warning(disable : 4996)
#pragma once

#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

#define ORIGINAL_IMAGE  "ORIGINAL IMAGE"
#define EMBOSSING		"EMBOSSING"

Mat embossingFilter(const Mat & src, int grayscale);
Mat embossingFilter(const Mat & src);
