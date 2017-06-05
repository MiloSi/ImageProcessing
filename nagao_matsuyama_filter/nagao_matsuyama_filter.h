#pragma once
#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;


Mat nagaoMatsuyamFilter(const Mat src);

#define ORIGINAL_IMAGE	   "ORIGIANL IMAGE"
#define NAGAO_MATSUYAMA	   "MAGAO MATSUYAMA"