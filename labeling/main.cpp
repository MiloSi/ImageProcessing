#pragma warning (disable : 4996)
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS 1

#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <vector>
#include <hash_map>

using namespace std;
using namespace cv;

#define MAX		 255
#define ZERO_VALUE 65536


// 2 - Scan labeling

/*
	Created by Milo Si (Called me C)
*/

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

	threshold(image, image, 128, 255, THRESH_BINARY_INV);
	Mat label(image.rows, image.cols, CV_32S, Scalar(0));
	

	vector<Point2i> v;

	int value = 0;

	// first scan

	for (int x = 0; x < image.cols; x++) 
	{
		if (image.at<uchar>(0, x) == MAX)
		{
			if (x == 0) {
				label.at<int>(0, x) = ++value;
			//	v.push_back.push_back(Point2i(value, value));
			
				continue;
			}
			label.at<int>(0, x) = (label.at<int>(0, x - 1) == 0) ? ++value : value;
		}
	}

	for (int y = 1; y < image.rows -1; y++)
	{
		for (int x = 0; x < image.cols-1; x++)
		{
			if (image.at<uchar>(y, x) == MAX) {

				if (x == 0) {

					if ((label.at<int>(y - 1, x) != 0))
					{
						label.at<int>(y, x) = label.at<int>(y - 1, x);
					}
					else
					{
						label.at<int>(y, x) = ++value;
				
					//	v.push_back(Point2i(value, value));
					}
					
					//label.at<int>(y, x) = (label.at<int>(y - 1, x) != 0) ? label.at<int>(y - 1, x) : ++value;
					//v.push_back(Point2i(value, value));
				}

				else {
					int up = label.at<int>(y - 1, x);
					int left = label.at<int>(y, x - 1);
					
					
					//	int diag = label.at<int>(y - 1, x - 1);

					
				
					if (up == 0) up = ZERO_VALUE;
					if (left == 0) left = ZERO_VALUE;
					

					int near = (up < left) ? up : left;
				

					if (near == ZERO_VALUE)
					{
						label.at<int>(y, x) = ++value;
						
						//v.push_back(Point2i(value, value));
						continue;

					}
					label.at<int>(y, x) =  near;
			
				}

			}
		}
	}

	// second scan



	for (int y = image.rows-2; y >= 0 ; y--)
	{
		for (int x = image.cols - 1; x >= 0; x--)
		{
			if (image.at<uchar>(y, x) == MAX) {

				if (x == image.cols - 1) {
					if (label.at<int>(y + 1, x) < label.at<int>(y, x))
					{
					
						label.at<int>(y, x) = label.at<int>(y + 1, x);
					}

				//	label.at<int>(y, x) = 
				//		(label.at<int>(y+ 1, x) <  label.at<int>(y,x)) ? label.at<int>(y + 1, x) : label.at<int>(y, x);
				}

				else {
					int down = label.at<int>(y + 1, x);
					int right = label.at<int>(y, x + 1);
					//int diag = label.at<int>(y + 1, x + 1);

					if (down == 0) down = ZERO_VALUE;
					if (right == 0) right = ZERO_VALUE;
					//if (diag == 0) diag = ZERO_VALUE;

					int near = (down <  right) ? down : right;
					//near = (near < diag) ? near : diag;

					if (label.at<int>(y, x) > near)
					{
					
						label.at<int>(y, x) = near;
					}
				}
			}
		}
	}

	Mat dst(label.rows, label.cols, CV_8UC3, Scalar(0, 0, 0));
	for (int y = 0; y < dst.rows; y++)
	{
		for (int x = 0; x < dst.cols; x++)
		{
			dst.at<Vec3b>(y, x)[0] = label.at<int>(y, x) * 64 % 255;
			dst.at<Vec3b>(y, x)[1] = label.at<int>(y, x) * 92 % 255;
			dst.at<Vec3b>(y, x)[2] = label.at<int>(y, x) * 155 % 255;
		}
	}

	imshow("src", image);
	imshow("dst", dst);
	waitKey(0);
}