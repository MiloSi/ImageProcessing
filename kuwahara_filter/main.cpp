#include "kuwahara_filter.h"


/*
	Created by Milo Si

	Kuwahara Filtering

*/

int main(int argc, char ** argv)
{
	string imageName = "lena.jpg";
	//string imageName = "board.jpg";
	if (argc >= 2) imageName = argv[1];


	
#if 0
	Mat image = imread(imageName, IMREAD_COLOR);
	Mat dst = kuwaharaFilter(image);
#else
	Mat image = imread(imageName, IMREAD_GRAYSCALE);
	Mat dst = kuwaharaFilter(image, 0);
#endif


	namedWindow(ORIGINAL_IMAGE);
	namedWindow(KUWAHARA);

	moveWindow(ORIGINAL_IMAGE, 0, 0);
	moveWindow(KUWAHARA, image.cols, 0);

	imshow(ORIGINAL_IMAGE, image);
	imshow(KUWAHARA, dst);

	waitKey(0);

	return 0;
}