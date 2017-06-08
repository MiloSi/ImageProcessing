#pragma warning (disable : 4996)
#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>


using namespace std;
using namespace cv;

int main(int argc, char ** argv)
{

	String fileName  = "lena.jpg";
	Mat src= imread(fileName, IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "NO FILE " << endl;
		return 0;
	}


	int histSize = 256; // bin size
	float range[] = { 0, 255 };
	const float *ranges[] = { range };
	// Calculate histogram
	Mat hist;
	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	// Normalize the result to [ 0, histImage.rows]
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i< histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	namedWindow("Result", 1); imshow("Result", histImage);
	waitKey(0);



	Mat dpcm(src.rows, src.cols, CV_32SC1, Scalar(0));


	for (int y = 0; y < src.rows; y++)
	{
		int *ptr = dpcm.ptr<int>(y);
		uchar *iPtr = src.ptr<uchar>(y);
		for (int x = 0; x < src.cols; x++)
		{
			if (x == 0)
				ptr[0] = iPtr[0];
			else
				ptr[x] = iPtr[x - 1] - iPtr[x] + 256;
		}
	}


	int histSize1 = 512; // bin size
	float range1[] = {0, 512 };
	const float *ranges1[] = { range1 };
	// Calculate histogram
	//Mat hist;


	hist = Mat(1, 512, CV_32FC1, Scalar(0));
	float *histptr = hist.ptr<float>(0);
	for (int y = 0; y < src.rows; y++)
	{
		int *ptr = dpcm.ptr<int>(y);
		for (int x = 0; x < src.cols; x++)
		{
			histptr[ptr[x]]++;
		}
	}
	
	cout << hist << endl;


	hist_w = 512; hist_h = 400;
	bin_w = cvRound((double)hist_w / 512);
	histImage = Mat(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	// Normalize the result to [ 0, histImage.rows]
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i< 512; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	namedWindow("Result", 1); imshow("Result", histImage);
	waitKey(0);



	Mat dst(src.rows, src.cols, src.type());

	for (int y = 0; y < src.rows; y++)
	{
		int *ptr = dpcm.ptr<int>(y);
		uchar *iPtr = dst.ptr<uchar>(y);
		for (int x = 0; x < src.cols; x++)
		{
			if (x == 0)
				iPtr[0] = ptr[0];
			else
				iPtr[0] = ptr[x - 1] + iPtr[x];
		}
	}

}