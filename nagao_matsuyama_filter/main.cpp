#include "nagao_matsuyama_filter.h"

/*
	Created by Milo Si (Or C)

	Nagao Matsuyam Filtering
	I extended kuwahara code to nagao_matsuyama code
*/

int main(int argc, char ** argv)
{
	string imageName = "lena.jpg";
	//string imageName = "board.jpg";
	if (argc >= 2) imageName = argv[1];

	Mat image = imread(imageName, IMREAD_COLOR);
	Mat dst = nagaoMatsuyamFilter(image);

	namedWindow(ORIGINAL_IMAGE);
	namedWindow(NAGAO_MATSUYAMA);

	moveWindow(ORIGINAL_IMAGE, 0, 0);
	moveWindow(NAGAO_MATSUYAMA, image.cols, 0);

	imshow(ORIGINAL_IMAGE, image);
	imshow(NAGAO_MATSUYAMA, dst);

	waitKey(0);

	imwrite("nagao_matsuyama.jpg", dst);

	return 0;
}