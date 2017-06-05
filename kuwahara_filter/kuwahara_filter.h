#pragma once
#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

Mat kuwaharaFilter(const Mat& src);
Mat kuwaharaFilter(const Mat& src, int grayscale);


#define ORIGINAL_IMAGE "ORIGIANL IMAGE"
#define KUWAHARA	   "KUWAHARA"