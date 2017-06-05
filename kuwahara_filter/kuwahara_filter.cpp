#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

Mat kuwaharaFilter(const Mat& src);

#define ORIGINAL_IMAGE "ORIGIANL IMAGE"
#define KUWAHARA	   "KUWAHARA"


Vec3d getAverage(Mat src)
{
	Vec3d average = { 0., 0., 0. };

	for (int i = 0; i < 3; i++) {
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				average[i] += src.at<Vec3b>(y, x)[i];

			}
		}
		average[i] = average[i] / 9;
	}
	return average;
}
Vec3d getVariance(Mat src, Vec3d average)
{
	
	Vec3d variance = { 0., 0., 0. };
	for (int i = 0; i < 3; i++) {
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				variance[i] += pow(src.at<Vec3b>(y, x)[i] - average[i],2);

			}
		}
		variance[i] = variance[i] / 9;
	}
	return variance;
}

Vec3b minVarianceLocation(Vec3d v[4]) {
	Vec3b min;
	int index = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 4; j++)
		{
			if (v[index][i] > v[j][i]) {
				index = j;
			}
		}
		min[i] = index;
	}

	return min;
}


Mat kuwaharaFilter(const Mat& src) {

	Mat dst(src.rows, src.cols, src.type(), Scalar(0,0,0));


	for (int y = 2; y < src.rows - 2; y++)
	{
		for (int x = 2; x < src.cols - 2; x++)
		{
			Mat region[4];
			Vec3d average[4];
			Vec3d variance[4];


			region[0] = Mat(src, Rect(x - 2, y - 2, 3, 3));
			region[1] = Mat(src, Rect(x, y - 2, 3, 3));
			region[2] = Mat(src, Rect(x - 2, y, 3, 3 ));
			region[3] = Mat(src, Rect(x, y, 3, 3));

		
			for (int i = 0; i < 4; i++)
			{
				average[i] = getAverage(region[i]);
				variance[i] = getVariance(region[i], average[i]);

			}

			Vec3b minLocation = minVarianceLocation(variance);
			for (int i = 0; i < 3; i++)
			{
				dst.at<Vec3b>(y, x)[i] = saturate_cast<uchar>(average[minLocation[i]][i] + 0.5);

			}
		
		}
	}
	return dst;
}




double getAverage(Mat src, int a)
{
	double average = 0;


	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			average += (double)src.at<uchar>(y, x);
		}
	}
	average = average / 9;

	return average;
}


double getVariance(Mat src, double average)
{
	double variance = 0;


	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			variance = pow(src.at<uchar>(y, x) - average, 2);

		}
	}
	variance = variance / 9;

	return variance;
}

int minVarianceLocation(double v[4])
{
	int index = 0;

	for (int j = 1; j < 4; j++)
	{
		if (v[index] > v[j]) {
			index = j;
		}
	}

	return index;
}


Mat kuwaharaFilter(const Mat& src, int grayscale) {

	Mat dst(src.rows, src.cols, src.type(), Scalar(0));


	for (int y = 2; y < src.rows - 2; y++)
	{
		for (int x = 2; x < src.cols - 2; x++)
		{
			Mat region[4];
			double average[4];
			double variance[4];


			region[0] = Mat(src, Rect(x - 2, y - 2, 3, 3));
			region[1] = Mat(src, Rect(x, y - 2, 3, 3));
			region[2] = Mat(src, Rect(x - 2, y, 3, 3));
			region[3] = Mat(src, Rect(x, y, 3, 3));


			for (int i = 0; i < 4; i++)
			{
				average[i] = getAverage(region[i], 0);
				variance[i] = getVariance(region[i], average[i]);

			}

			int minLocation = minVarianceLocation(variance);
			for (int i = 0; i < 3; i++)
			{
				dst.at<uchar>(y, x) = saturate_cast<uchar>(average[minLocation] + 0.5);

			}

		}
	}
	return dst;
}


