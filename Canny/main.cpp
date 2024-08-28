#include "opencv2\opencv.hpp"
#include <stdint.h>

using namespace cv;
using namespace std;

int lowThreshold = 10;
const int ratio = 3;

int main()
{
	Mat img = imread("Cube.png");
	Mat originalFrame;
	Mat can;
	cvtColor(img, img, CV_BGR2GRAY);

	char key = (char)waitKey(40);
	while (key != 'j' || key != 'J')
	{
		key = (char)waitKey(40);
		img.copyTo(originalFrame);
		key = (char)waitKey(40);
		if (key == 'l' || key == 'L')
		{
			lowThreshold = lowThreshold < 100 ? lowThreshold + 15 : 10;
			cout << "lThreshold = " << lowThreshold << endl;
		}
		Canny(img, can, lowThreshold, lowThreshold*ratio, 3);
		imshow("cannyFrame", can);
		imshow("originalFrame", originalFrame);
		waitKey(40);
	}
	return 1;

}

