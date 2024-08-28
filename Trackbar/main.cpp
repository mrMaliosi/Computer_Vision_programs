//https://docs.opencv.org/3.4/da/d6a/tutorial_trackbar.html 
#include "opencv2\opencv.hpp"
#include <stdint.h>
#include <iostream>

using namespace cv;
using namespace std;

Mat nti;
Mat HSVnti;
Mat HSVntiBin;

int hMin, hMax, sMin, sMax, vMin, vMax;

static void Binariz(int, void*)
{

	//������������ (� �� ����), ��������� ������� ���������
	inRange(HSVnti, Scalar(hMin, sMin, vMin), Scalar(hMax, sMax, vMax), HSVntiBin); //inRange(HSVnti, Scalar(10, 0, 50), Scalar(30, 255, 255), HSVntiBin);

	//imshow("HSV", HSVnti);
	imshow("Original", nti);
	imshow("Bin", HSVntiBin);

}

int main(void)
{
	nti = imread("S_1.jpg");
	cvtColor(nti, HSVnti, CV_BGR2HSV);

	hMin = 0;
	hMax = 180;
	sMin = 0;
	sMax = 255;
	vMin = 0;
	vMax = 255;

	namedWindow("Bin", WINDOW_AUTOSIZE); // Create Window

	//������� ������� hMin
	char TrackbarName[130];
	sprintf(TrackbarName, "hMin", hMax);
	createTrackbar(TrackbarName, "Bin", &hMin, hMax, Binariz);

	//������� ������� hMax
	sprintf(TrackbarName, "hMax", hMax);
	createTrackbar(TrackbarName, "Bin", &hMax, hMax, Binariz);

	//������� ������� sMin
	sprintf(TrackbarName, "sMin", sMax);
	createTrackbar(TrackbarName, "Bin", &sMin, sMax, Binariz);

	//������� ������� sMax
	sprintf(TrackbarName, "sMax", sMax);
	createTrackbar(TrackbarName, "Bin", &sMax, sMax, Binariz);

	//������� ������� vMin
	sprintf(TrackbarName, "vMin", vMax);
	createTrackbar(TrackbarName, "Bin", &vMin, vMax, Binariz);

	//������� ������� vMax
	sprintf(TrackbarName, "vMax", vMax);
	createTrackbar(TrackbarName, "Bin", &vMax, vMax, Binariz);


	Binariz(hMin, 0); //�� ���������
	Binariz(sMin, 0); //�� ���������
	Binariz(vMin, 0); //�� ���������

	waitKey(0);
	return 0;
}
