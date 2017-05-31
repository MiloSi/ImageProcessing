#pragma warning (disable : 4996)
#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

/*
Created by Milo Si (called me C)
Window base match
*/

#define RIGHT_IMAGE "RIGHT IMAGE"
#define LEFT_IMAGE  "LEFT IMAGE"
#define DISPARITY_IMAGE "DISPARITY IMAGE" 

int main(int argc, char** argv)
{
	String leftImageName = "scene1.row3.col2.ppm";
	String rightImageName = "scene1.row3.col3.ppm";

	if (argc >= 2)
	{
		leftImageName = argv[2];
		rightImageName = argv[3];
	}

	Mat leftImage = imread(leftImageName, IMREAD_GRAYSCALE);
	Mat rightImage = imread(rightImageName, IMREAD_GRAYSCALE);

	Mat dst(leftImage.rows, leftImage.cols, CV_8UC1);

	if (leftImage.empty() || rightImage.empty())
	{
		cerr << "CAN'T FIND FILE" << endl;
		return 0;
	}

	//these are used to make window
	int fromX;
	int fromY;
	int width;
	int height;

	double tempMin;
	double min;

	int distance;


	//Window Size is 5
	for (int y = 0; y < rightImage.rows; y++)
	{
		for (int x = 0; x < rightImage.cols; x++)
		{


			fromX = x - 2;
			fromY = y - 2;
			width = x + 3;
			height = y + 3;

			if (width > rightImage.cols - 1) width = rightImage.cols - 1;
			if (height > rightImage.rows - 1) height = rightImage.rows - 1;

			if (fromX < 0)	fromX = 0;
			if (fromY < 0)  fromY = 0;
			width = width - fromX;
			height = height - fromY;

			Mat rightWindow(rightImage, Rect(fromX, fromY, width, height));

			min = 655360;
			distance = x;
			for (int swift = fromX; swift < fromX + 16; swift++)
			{
				if (swift + width > rightImage.cols - 1)
					break;
				Mat leftWindow(leftImage, Rect(swift, fromY, width, height));
				tempMin = 0;
				for (int y1 = 0; y1 < height; y1++)
				{
					for (int x1 = 0; x1 < width; x1++)
					{
						tempMin += pow((double)leftWindow.at<uchar>(y1, x1) - (double)rightWindow.at<uchar>(y1, x1), 2);
					}
				}
				if (min > tempMin)
				{
					distance = swift;
					min = tempMin;
				}
			}

			dst.at<uchar>(y, x) = saturate_cast<uchar>((distance - x) * 16); // get subtract from distance to x and Normalization.

		}
	}

	namedWindow(RIGHT_IMAGE);
	namedWindow(LEFT_IMAGE);
	namedWindow(DISPARITY_IMAGE);

	moveWindow(RIGHT_IMAGE, 0, 0);
	moveWindow(LEFT_IMAGE, rightImage.cols, 0);
	moveWindow(DISPARITY_IMAGE, rightImage.cols * 2, 0);

	imshow(RIGHT_IMAGE, rightImage);
	imshow(LEFT_IMAGE, leftImage);
	imshow(DISPARITY_IMAGE, dst);

	waitKey(0);
}