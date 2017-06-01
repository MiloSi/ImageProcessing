#pragma warning (disable : 4996)
#include <iostream>
#include <opencv2\opencv.hpp>

using namespace std;
using namespace cv;


int main()
{
	String imageName = "Girl_in_front_of_a_green_background.jpg";
	String sample = "greens.jpg";
	String backgroundName = "graf1.png";

	Mat image = imread(imageName, IMREAD_COLOR);
	Mat background = imread(backgroundName, IMREAD_COLOR);

	Mat dst(image.rows, image.cols, image.type());


	resize(background, background, Size(image.cols, image.rows));


	int threshold;
	int alpha;
	int beta;

	Mat convert(image.rows, image.cols, CV_32FC3);




	cvtColor(image, convert, CV_BGR2YCrCb);

	GaussianBlur(convert, convert, Size(3, 3), 1); 


	Mat cb(image.rows, image.cols, CV_8U);
	Mat cr(image.rows, image.cols, CV_8U);

	for (int y = 0; y < convert.rows; y++)
	{
		for (int x = 0; x < convert.cols; x++)
		{
			cb.at<uchar>(y, x) = convert.at<Vec3b>(y, x)[2];
			cr.at<uchar>(y, x) = convert.at<Vec3b>(y, x)[1];
		}
	}

	int  histCb[256] = { 0, };
	int  histCr[256] = { 0, };


	for (int y = 0; y < convert.rows; y++)
	{
		for (int x = 0; x < convert.cols; x++)
		{
			int b = cb.at<uchar>(y, x);
			int r = cr.at<uchar>(y, x);

			histCb[b]++;
			histCr[r]++;
		}
	}
	int key_cb = 0;
	int key_cr = 0;


	for (int i = 0; i < 255; i++)
	{
		if (histCb[key_cb] < histCb[i])
			key_cb = i;
		if (histCr[key_cr] < histCr[i])
			key_cr = i;
	}


	int inner = 38 ;
	int outer = 45;



	for (int y = 0; y < convert.rows; y++)
	{
		for (int x = 0; x < convert.cols; x++)
		{


			threshold = sqrt(pow((double)convert.at<Vec3b>(y, x)[2] - key_cb, 2) + pow((double)convert.at<Vec3b>(y, x)[1] - key_cr, 2));
			
			if (threshold < inner) {
				alpha = 1;
			}
			else if (threshold > outer)
			{
				alpha = 0;
			}
			else
			{
				alpha = (threshold - inner) / ( outer- inner);
			}
			dst.at<Vec3b>(y, x)[0] = alpha * background.at<Vec3b>(y, x)[0] + (1 - alpha) * image.at<Vec3b>(y, x)[0];
			dst.at<Vec3b>(y, x)[1] = alpha * background.at<Vec3b>(y, x)[1] + (1 - alpha) * image.at<Vec3b>(y, x)[1];
			dst.at<Vec3b>(y, x)[2] = alpha * background.at<Vec3b>(y, x)[2] + (1 - alpha) * image.at<Vec3b>(y, x)[2];
		
		}
	}

	medianBlur(dst, dst, 3);

	imshow("dst", dst);
	cv::waitKey(0);


	return 0;

}