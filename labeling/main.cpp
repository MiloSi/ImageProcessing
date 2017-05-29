#pragma warning (disable : 4996)
#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <vector>

using namespace std;
using namespace cv;

#define MAX		 255
#define ZERO_VALUE 65536


// 2 - Scan labeling
int main(int argc, char** argv)
{
	String fileName = "pic1.png";

	if (argc == 2)
		fileName = argv[1];

	Mat image = imread(fileName, IMREAD_GRAYSCALE);

	if (image.empty())
	{
		cerr << "CAN'T FIND FILE NAME" << endl;
		return 0;
	}

	threshold(image, image, 128, 255, THRESH_BINARY);
	Mat label(image.rows, image.cols, CV_32S, Scalar(0));

	vector<Point2i> v;

	int value = 1;

	// first scan

	for (int x = 0; x < image.cols; x++) 
	{
		if (image.at<uchar>(0, x) == MAX)
		{
			if (x == 0)
				continue;
			label.at<int>(0, x) = (label.at<int>(0, x - 1) == value) ? value : ++value;
		}
	}

	for (int y = 1; y < image.rows; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			if (image.at<uchar>(y, x) == MAX) {

				if (x == 0) {
					label.at<int>(y, x) = (label.at<int>(y - 1, x) != 0) ? label.at<int>(y - 1, x) : ++value;
				}

				else {
					int up = label.at<int>(y - 1, x);
					int left = label.at<int>(y, x - 1);
					int diag = label.at<int>(y - 1, x - 1);

					
				
					if (up == 0) up = ZERO_VALUE;
					if (left == 0) left = ZERO_VALUE;
					if (diag == 0) diag = ZERO_VALUE;

					int near = (up < left) ? (up < diag) ? up : diag : (left < diag) ? left  : diag;
					label.at<int>(y, x) = (near == ZERO_VALUE) ? ++value : near;
			
				}

			}
		}
	}

	// second scan



	for (int y = 0; y < image.rows -1 ; y++)
	{
		for (int x = 0; x < image.cols; x++)
		{
			if (image.at<uchar>(y, x) == MAX) {

				if (x == image.cols - 1) {
					label.at<int>(y, x) = 
						(label.at<int>(y+ 1, x) <  label.at<int>(y,x)) ? label.at<int>(y + 1, x) : label.at<int>(y, x);
				}

				else {
					int down = label.at<int>(y + 1, x);
					int right = label.at<int>(y, x + 1);
					int diag = label.at<int>(y + 1, x + 1);

					if (down == 0) down = ZERO_VALUE;
					if (right == 0) right = ZERO_VALUE;
					if (diag == 0) diag = ZERO_VALUE;

					int near = (down < right) ? (down < diag) ? down : diag : (right < diag) ? right : diag;
					label.at<int>(y, x) = (label.at<int>(y, x) < near) ? label.at<int>(y, x) : near;
				}

			}
		}
	}

}