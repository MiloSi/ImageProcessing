#pragma warning (disable : 4996)
#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

void showHistogram(Mat hist, int histSize);
void histogram(Mat src, int histSize, const float range[])
{
	Mat hist;
	const float * ranges[] = { range };

	calcHist(&src, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false);

	showHistogram(hist, histSize);
}

void showHistogram(Mat hist, int histSize)
{
	int hist_w = 512; int hist_h = 200;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	for (int i = 1; i< histSize; i++)
	{
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);
	}
	namedWindow("Result", 1); imshow("Result", histImage);
	waitKey(0);
}



int main(int argc, char ** argv)
{

	String fileName  = "lena.jpg";
	Mat src= imread(fileName, IMREAD_GRAYSCALE);

	if (src.empty())
	{
		cerr << "NO FILE " << endl;
		return 0;
	}
	float range[] = { 0.f, 255.f };
	histogram(src, 256, range);

	Mat dpcm(src.rows, src.cols, CV_32SC1, Scalar(0));

	/*
	Mat minusHist(1, 255, CV_32FC1, Scalar(0)); //MINUS Is 255
	Mat plusHist(1, 256, CV_32FC1, Scalar(0)); // PLUS Is 256
	*/
	Mat dpcmHist(1, 512, CV_32FC1, Scalar(0));

	for (int y = 0; y < src.rows; y++)
	{
		int *ptr = dpcm.ptr<int>(y);
		uchar *iPtr = src.ptr<uchar>(y); 
		for (int x = 0; x < src.cols; x++)
		{
			if (x == 0) {
				ptr[0] = iPtr[0];

			}
			else {
				ptr[x] = iPtr[x - 1] - iPtr[x];
				dpcmHist.at<float>(0, ptr[x] + 256)++;
			}
		}
	}
	showHistogram(dpcmHist, 512);

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
				iPtr[x] = iPtr[x -1] - ptr[x];
		}
	}
	histogram(dst, 256, range);

}