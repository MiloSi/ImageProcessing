
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
#define IMPULSE_NOSIE		 "IMPULSE_NOSIE"


Mat saltAndPepperNoise(const Mat& src, double ratio)
{
	ratio = (ratio > 100) ? 100 : (ratio > 0) ? ratio : 0;

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
		
	Mat noise = saltAndPepperNoise(originalFile, ratio);


	namedWindow(ORIGINAL_WIONDOW);
	namedWindow(IMPULSE_NOSIE);
	moveWindow(ORIGINAL_WIONDOW, 0, 0);
	moveWindow(IMPULSE_NOSIE, originalFile.cols, 0);


	imshow(ORIGINAL_WIONDOW, originalFile);
	imshow(IMPULSE_NOSIE, noise);

	waitKey(0);


	return 0;
}