#include "bilateral_filter.h"








Mat bilateralFilter(const Mat & src, const double spaceSigma, const double distanceSigma)
{
	Mat dst(1, 1, CV_64FC1);
	return dst;
}

Mat getGaussianMask(int size, const double sigma)
{
	Mat dst(size, size, CV_64FC1);

	int center = size >> 1;
	float kernel_x;
	float kernel_y;

	for (int y = 0; y < size; y++)
	{
		for (int x = 0; x < size; x++)
		{
			kernel_x = x - center;
			kernel_y = y - center;

			dst.at<double>(y, x) =
				exp(-(pow(kernel_y, 2) + pow(kernel_x, 2)) / (2 * sigma * sigma))
					/ (2. * CV_PI * sigma * sigma);

		}
	}

	return dst;

}


Mat bilateralFilter(const Mat & src, const double spaceSigma, const double distanceSigma, const int grayscale)
{
	Mat dst(src.rows, src.rows, src.type(), Scalar(0));

	int sigmaMax = (spaceSigma < distanceSigma) ? distanceSigma : spaceSigma;
	int radius = sigmaMax * 2;
	int size = radius * 2 + 1;

	double distance2 = distanceSigma * distanceSigma * 2;

	double weight;
	double totalWeight;

	double sum;

	uchar value;

	int yMax;
	int xMax;
	int x1;
	int y1;

	Mat gaussianMask = getGaussianMask(size, spaceSigma);
	Mat gaussSimlarity(1, 256, CV_64FC1);


	double *ptr = gaussSimlarity.ptr<double>(0);
	for (int i = 0; i < 256; i++)
		ptr[i] = exp(double(-i / distance2));


	for (int y = 1; y < src.rows - 1; y++)
	{
		for (int x = 1; x < src.cols - 1; x++)
		{

			totalWeight = 0;
			sum = 0;
			xMax = x + radius;
			yMax = y + radius;



			for (int j = y - radius; j < yMax; j++)
			{
				for (int i = x - radius; i < xMax; i++)
				{

					if (j >= 0 && i >= 0 && j < src.rows && i < src.cols) {

						x1 = i + radius;
						y1 = j + radius;

						weight = gaussianMask.at<double>(y1 - y, x1 - x) * ptr[abs(src.at<uchar>(y, x) - src.at<uchar>(j, i))];

						sum += weight *src.at<uchar>(j, i);
						totalWeight += weight;

					}
				}
			}
	
			dst.at<uchar>(y, x) = (uchar)(sum / totalWeight);
		}
	}

	return dst;

}