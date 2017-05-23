#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

/*
	Created by Milo Si (Called me C)
	
	bit plane project
*/

int main(int argc, char** argv)
{
	String originalFileName = "lena.jpg";
	String secretFileName = "bat.png";

	Mat original = imread(originalFileName, IMREAD_GRAYSCALE);
	Mat secret = imread(secretFileName, IMREAD_GRAYSCALE);

	if (original.empty() || secret.empty())
	{
		cerr << "CAN'T FIND FILES" << endl;
		return 0;
	}


	Mat dst(original.rows, original.cols, CV_8UC1, Scalar(0));

	resize(secret, secret, Size(original.cols, original.rows));

	threshold(secret, secret, 100, 255, THRESH_BINARY);

	for (int y = 0; y < original.rows; y++)
	{
		uchar *ptr = dst.ptr<uchar>(y);
	  
		for (int x = 0; x < original.cols; x++)
		{
			ptr[x] = (secret.at<uchar>(y, x) == 255) ?
				(original.at<uchar>(y,x) | (uchar)0x001) : ((original.at<uchar>(y,x) >> 1) << 1);
		}
	}

	namedWindow("BIT PLANE");
	moveWindow("BIT PLANE", 0, 0);

	uchar swift = 0;
	while (swift <= 7)
	{
		Mat show(dst.rows, dst.cols, CV_8UC1);

		for (int y = 0; y < original.rows; y++)
		{
			for (int x = 0; x < original.cols; x++)
			{
				show.at<uchar>(y, x) = (dst.at<uchar>(y, x) & (128 >> swift)) ?
					255 : 0;
			}
		}
		
		imshow("BIT PLANE", show);
		waitKey(0);
		swift++;
	}
	return 0;

}