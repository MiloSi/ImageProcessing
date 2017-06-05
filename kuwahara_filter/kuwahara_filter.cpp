#include <iostream>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>

using namespace std;
using namespace cv;

Mat kuwaharaFilter(const Mat& src);



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
			if (v[index][i] < v[j][i]) {
				index = j;
			}
		}
		min[i] = index;
	}

	return min;


}


Mat kuwaharaFilter(const Mat& src) {

	Mat dst(src.rows, src.cols, src.type(), Scalar(0,0,0));


	for (int y = 2; y < src.rows - 3; y++)
	{
		for (int x = 2; x < src.cols - 3; x++)
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





int main(int agrc, char ** argv)
{
	string imageName ="lena.jpg";
	Mat image = imread(imageName, IMREAD_COLOR);
	
	
	Mat dst = kuwaharaFilter(image);


	imshow("src", image);
	imshow("dst", dst);

	waitKey(0);

	return 0;
}