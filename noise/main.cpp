
#pragma warning (disable : 4996)
#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

/*
	Created by Milo C (called me C)

	Noise added
*/

#define ORIGINAL_WIONDOW	 "ORIGINAL WINDOW"
#define IMPULSE_NOSIE		 "IMPULSE NOSIE"
#define GAUSSIAN_NOISE		 "GAUSSIAN NOISE"


template<typename T>
inline T RANGE(T ratio) {return (ratio > 100) ? 100 : (ratio > 0) ? ratio : 0;}

Mat saltAndPepperNoise(const Mat& src, double ratio)
{
	ratio = RANGE<double>(ratio);

	Mat dst = src.clone();
	int number = (ratio * src.cols * src.rows / 100);
	bool whiteOrBlack = true;
	while (number > 0)
	{
		int x = rand() % src.cols;
		int y = rand() % src.rows;

		if(whiteOrBlack)
			dst.at<uchar>(y, x) = 255;
		else
			dst.at<uchar>(y, x) = 0;

		whiteOrBlack = !whiteOrBlack;
		number--;
	}
	
	return dst;
}


Mat gaussianNoise(const Mat& src, double ratio)
{
	ratio = RANGE<double>(ratio);

	Mat dst = src.clone();
	int number = (ratio * src.cols * src.rows / 100);
	bool whiteOrBlack = true;

	double r1;
	double r2;
	double normal;
	double stdNormal;

	while (number > 0)
	{
		int x = rand() % src.cols;
		int y = rand() % src.rows;

		r1 = (double)rand() / RAND_MAX;
		r2 = (double)rand() / RAND_MAX;
		
		normal = sqrt(-2.0 * log(r1)) * cos(2 * CV_PI * r2);
		stdNormal = (double)dst.at<uchar>(y, x) + (normal * 10.0);

		if (stdNormal > 255) dst.at<uchar>(y, x) = 255;
		else if (stdNormal < 0) dst.at<uchar>(
			y, x) = 0;
		else dst.at<uchar>(y, x) = (uchar)stdNormal;

		
		number--;
	}

	return dst;
}

int main(int argc, char ** argv)
{
	String fileName = "lena.jpg";
	double ratio = 10.0;

	if (argc > 1)
	{
		fileName = argv[1];
		ratio = atof(argv[2]);
	}

	Mat originalFile = imread(fileName, IMREAD_GRAYSCALE);
	if (originalFile.empty())
	{
		cerr << "CAN'T FIND FILE ";
		return 0;
	}
		
	Mat impulse_noise = saltAndPepperNoise(originalFile, ratio);
	Mat gaussian_noise = gaussianNoise(originalFile, ratio);

	namedWindow(ORIGINAL_WIONDOW);
	namedWindow(IMPULSE_NOSIE);
	namedWindow(GAUSSIAN_NOISE);

	moveWindow(ORIGINAL_WIONDOW, 0, 0);
	moveWindow(IMPULSE_NOSIE, originalFile.cols, 0);
	moveWindow(GAUSSIAN_NOISE, originalFile.cols * 2, 0);

	imshow(ORIGINAL_WIONDOW, originalFile);
	imshow(IMPULSE_NOSIE, impulse_noise);
	imshow(GAUSSIAN_NOISE, gaussian_noise);

	waitKey(0);


	return 0;
}