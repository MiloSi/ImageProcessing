#include "bilateral_filter.h"

/*
	Created by Milo Si
	Bilateral Filter.

	It was hard to understand bilateral filter.
	So I searched many documents, but I could not understand.

	finally, I read the code from http://code.google.com/p/bilateralfilter/ many times. 
	I learned how bilateral filter worked. 

	So, my code is very similar to http://code.google.com/p/bilateralfilter/
	


*/


int main(int agrc, char ** argv)
{
	string fileName = "lena.jpg";
	Mat src = imread(fileName, IMREAD_GRAYSCALE);

#if 1
	Mat dst = bilateralFilter(src, 10, 5, GRAYSCLAE);

#else 
	Mat dst;
	cv::bilateralFilter(src, dst, -1, 10, 5);
#endif

	namedWindow(ORIGINAL_IMAGE);
	namedWindow(BILATERAL_IMAGE);

	moveWindow(ORIGINAL_IMAGE, 0, 0);
	moveWindow(BILATERAL_IMAGE, src.cols, 0);

	imshow(ORIGINAL_IMAGE, src);
	imshow(BILATERAL_IMAGE, dst);

	waitKey(0);

	imwrite("bilateral.jpg", dst);

	return 0;

}