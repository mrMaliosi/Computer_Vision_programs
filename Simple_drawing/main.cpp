#include "opencv2\opencv.hpp"
#include <stdint.h>

using namespace cv;
using namespace std;

int main()
{
	Point center;
	center.x = 150;
	center.y = 150;
	Mat img = imread("lena.jpg");
	Rect rp(100, 100, 200, 200);
	Mat roi = img(rp);
	circle(roi, center, 10, Scalar(0, 255, 0), FILLED, LINE_8);
	imshow("Original", roi);

	waitKey();
}

