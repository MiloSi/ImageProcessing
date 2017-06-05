#include "nagao_matsuyama_filter.h"


const int skips[9][2] = {
	{9,9}, {6,8}, {0, 6}, {0, 2}, {2,8}, 
	{2,6}, {0,8}, {2,6}, {0, 8}
};


Vec3d getAverage(Mat mat, int n)
{
	Vec3d average = { 0.,0.,0. };
	int skip[2];

	skip[0] = skips[n][0];
	skip[1] = skips[n][1];
	

	int count;
	
	for (int i = 0; i < 3; i++) 
	{
		count = 0;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{

				if (skip[0] == count || skip[1] == count) {
					count++;
					continue;
				}
				average[i] += (double) mat.at<Vec3b>(y, x)[i];

				count++;
			}
		}
		if (n == 0)
			average[i] = average[i] / 9;
		else
			average[i] = average[i] / 7;

	}

	return average;
}


Vec3d getVariance(Mat mat, Vec3d average, int n)
{
	Vec3d variance = { 0.,0.,0. };
	int skip[2];

	skip[0] = skips[n][0];
	skip[1] = skips[n][1];


	int count;

	for (int i = 0; i < 3; i++)
	{
		count = 0;
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{

				if (skip[0] == count || skip[1] == count) {
					count++;
					continue;
				}
				variance[i] += pow(mat.at<Vec3b>(y, x)[i] - average[i], 2);

				count++;
			}
		}
		if (n == 0)
			average[i] = average[i] / 9;
		else
			average[i] = average[i] / 7;

	}

	return variance;
}

Vec3b minVarianceLocation(Vec3d v[9]) {
	Vec3b min;
	int index = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j < 9; j++)
		{
			if (v[index][i] > v[j][i]) {
				index = j;
			}
		}
		min[i] = index;
	}

	return min;
}


Mat nagaoMatsuyamFilter(const Mat src)
{
	Mat dst(src.rows, src.cols, src.type(), Scalar(0,0,0));
	Mat mask[9];
	Vec3d average[9];
	Vec3d variance[9];


	for (int y = 2; y < src.rows - 2; y++)
	{
		for (int x = 2; x < src.cols - 2; x++)
		{
			
			mask[0] = Mat(src, Rect(x - 1, y - 1, 3, 3));
			mask[1] = Mat(src, Rect(x - 1, y - 2, 3, 3));
			mask[2] = Mat(src, Rect(x - 0, y - 1, 3, 3));
			mask[3] = Mat(src, Rect(x - 1, y - 0, 3, 3));
			mask[4] = Mat(src, Rect(x - 2, y - 1, 3, 3));
			mask[5] = Mat(src, Rect(x - 2, y - 2, 3, 3));
			mask[6] = Mat(src, Rect(x - 0, y - 2, 3, 3));
			mask[7] = Mat(src, Rect(x - 0, y - 0, 3, 3));
			mask[8] = Mat(src, Rect(x - 2, y - 0, 3, 3));

			for (int i = 0; i < 9; i++)
				average[i] = getAverage(mask[i], i);
			for (int i = 0; i < 9; i++)
				variance[i] = getVariance(mask[i], average[i],i);

			Vec3b minLocation = minVarianceLocation(variance);
			for (int i = 0; i < 3; i++)
			{
				dst.at<Vec3b>(y, x)[i] = saturate_cast<uchar>(average[minLocation[i]][i] + 0.5);

			}



		}
	}

	return dst;
}
