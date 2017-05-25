#pragma warning (disable : 4996)
#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	String leftImageName= "scene1.row3.col2.ppm";
	String rightImageName = "scene1.row3.col3.ppm";

	Mat leftImage = imread(leftImageName, IMREAD_GRAYSCALE);
	Mat rightImage = imread(rightImageName, IMREAD_GRAYSCALE);

	Mat dst(leftImage.rows, leftImage.cols, CV_8UC1);

	if (leftImage.empty() || rightImage.empty())
	{
		cerr << "CAN'T FIND FILE" << endl;
		return 0;
	}
	int fromX;
	int fromY;
	int width;
	int height;

	double tempMin;
	double min;

	int moved_x;

	int count = 0;

	for (int y = 0; y < rightImage.rows ; y++)
	{
		for (int x = 0; x < rightImage.cols; x++)
		{
			fromX = x - 2;
			fromY = y - 2;
			width = x + 3;
			height = y + 3;

			if (width > rightImage.cols - 1) width = rightImage.cols -1;
			if (height > rightImage.rows - 1) height = rightImage.rows - 1;

			if (fromX < 0)	fromX = 0;
			if (fromY < 0)  fromY = 0;
			width = width - fromX;
			height = height - fromY;

			Mat box(rightImage, Rect(fromX, fromY, width, height));

			min = 655360;
			moved_x = x;
			for (int swift = x; swift < x + 16; swift++)
			{
				if (swift + width > rightImage.cols - 1)
					break;
				Mat differ(leftImage, Rect(swift, fromY, width, height));
				tempMin = 0;
				for (int y1 = 0; y1 < height; y1++)
				{
					for (int x1 = 0; x1 < width; x1++)
					{
						tempMin += pow((double)differ.at<uchar>(y1, x1) - (double)box.at<uchar>(y1, x1), 2);
					}
				}
				if (min > tempMin)
				{
					moved_x = swift;
					min = tempMin;
				}
			}

			uchar result = saturate_cast<uchar>((moved_x - x) * 16);
			dst.at<uchar>(y, x) = result;

		}
	}

	imshow("dst", dst);

	waitKey(0);
}