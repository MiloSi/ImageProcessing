#include "embossing_filter.h"

Mat embossingFilter(const Mat & src) {

	Mat dst(src.rows, src.cols, CV_8UC3, Scalar(0,0,0));

	for (int y = 1; y < src.rows - 1; y++)
	{
		Vec3b* ptr = dst.ptr<Vec3b>(y);
		for (int x = 1; x < src.cols - 1; x++)
		{

			for (int i = 0; i < 3; i++)
			{
				ptr[x][i] = src.at<Vec3b>(y + 1, x + 1)[i] - src.at<Vec3b>(y - 1, x - 1)[i];
			}
	
		}
	}

	return dst;
}



Mat embossingFilter(const Mat & src, int grayscale) {
	Mat dst(src.rows, src.cols, CV_8UC1, Scalar(0));

	for (int y = 1; y < src.rows -1; y++)
	{
		uchar* ptr = dst.ptr<uchar>(y);
		for (int x = 1; x < src.cols -1; x++)
		{
			ptr[x] = src.at<uchar>(y + 1, x + 1) - src.at<uchar>(y - 1, x - 1);
		}
	}

	return dst;

}