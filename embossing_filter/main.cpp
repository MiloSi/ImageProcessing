#include "embossing_filter.h"

/*
	Created by Milo Si (or C)
	Embossing Filter.

*/



int main(int argc, char ** argv)
{
	string imageName = "lena.jpg";
	//string imageName = "board.jpg";
	if (argc >= 2) imageName = argv[1];


#if 0
	Mat image = imread(imageName, IMREAD_COLOR);
	Mat dst = embossingFilter(image);
#else
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	Mat dst = embossingFilter(image, 0);
#endif


	namedWindow(ORIGINAL_IMAGE);
	namedWindow(EMBOSSING);

	moveWindow(ORIGINAL_IMAGE, 0, 0);
	moveWindow(EMBOSSING, image.cols, 0);

	imshow(ORIGINAL_IMAGE, image);
	imshow(EMBOSSING, dst);

	waitKey(0);

	imwrite("embossing.jpg", dst);

	return 0;
}